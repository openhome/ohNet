/**
* The ohnet object is the single global object used by ohnet Services to
* facilitate actions and subscriptions. 
* @module ohnet
* @title ohnet
*/

if (typeof ohnet == "undefined" || !ohnet) {
    /**
    * The ohnet global namespace object.  If ohnet is already defined, the
    * existing ohnet object will not be overwritten so that defined
    * namespaces are preserved.
    * @class ohnet
    * @static
    */
    var ohnet = {};
}

/**
* Manages the subscriptions to the ohnet Services.
* Subscribed services are notified of property state changes.
* @namespace ohnet
* @class SubscriptionManager
* @static
*/
ohnet.subscriptionmanager = (function () {

    // Constants 
    var DEFAULT_SUBSCRIPTION_TIMEOUT_SEC = 1800;
    var WEBSOCKETRETRYATTEMPTS = 1; // The number if retries for websockets before falling back to long polling (does not include initial attempt).
    var RENEW_TRIGGER = 0.7; // The multiplier in which to send the renewal message. (Send renew message every RENEW_TRIGGER * DEFAULT_SUBSCRIPTION_TIMEOUT_SEC)
   
    // Private Variables
    var Debug = false; // A flag to enable debugging messages written to console
    var subscriptionTimeoutSeconds = -1; // The suggested timeout in seconds for each subscription.
	var clientId = ''; 
	var allowWebSockets = true; // A flag to force the subscription manager to always use long polling
    var StartedFunction, ErrorFunction, Debug, webSocketPort, webSocketLive = false, webSocketAttempts = 0, ws,lp;
    var services = {}, pendingServices = [], pendingPropertyUpdates = {};
    
    // Public Variables
    var running = false; // A flag to state if the Subscription Manager is running

    // Functions


    /**
    * Starts the timer to renew subscriptions. 
    * The actual subscription timeout is returned by the ohnet Service. 
    * subscriptionTimeoutSeconds is the suggested timeout sent to the server.
    * @method setSubscriptionTimeout
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Int} timeoutSeconds The actual subscription timeout
    */
    var setSubscriptionTimeout = function (subscriptionId, timeoutSeconds) {

        var service = services[subscriptionId];
        if (service) {
            var actualSubscriptionTimeoutMs = timeoutSeconds * 1000 * RENEW_TRIGGER;
			 var timer = setTimeout(function () {
                renewSubscription(subscriptionId);
            }, actualSubscriptionTimeoutMs);

            service.SubscriptionTimer = timer; // Keep a reference to the timer so we can clear it when the service unsubscribes

            if (Debug) {
                console.log("setSubscriptionTimeout/actualSubscriptionTimeoutMs:" + actualSubscriptionTimeoutMs);
            }
        }
    };


    /**
    * Calls SetValue of the property 
    * @method setPropertyUpdate
    * @param {Int} subscriptionId The subscription id of the service
    * @param {String} propertyName The property name to update
    * @param {String} propertyValue The new value of the property
    */
    var setPropertyUpdate = function (subscriptionId, propertyName, propertyValue) {
        var service = services[subscriptionId];
        if (service) {
            var property = service.serviceProperties[propertyName];
            if (property) {
                property.setValue(propertyValue);
            }
        }
    };

	/**
	* Remove the pending service and add it to the services with the 
	* subscription id generated from the node.
	* @method receiveSubscribeCompleted
	* @param {Int} subscriptionId The subscription id of the service
	* @param {String} udn The udn name
	* @param {String} service The Service name
	* @param {Object} xmlDoc The XML to traverse
	*/
	var receiveSubscribeCompleted = function (subscriptionId, udn,service,timeout) {
		
		for(var i = 0 ; i < pendingServices.length; i++)
		{
	    	var pendingService = pendingServices[i];
	    	
	    	if(pendingService.udn == udn && pendingService.serviceName == service)
	    	{
				services[subscriptionId] = pendingService;
				services[subscriptionId].subscriptionId = subscriptionId;
	    		pendingServices.splice(i,1);
	    		
				var service = services[subscriptionId];
			    if (service.serviceAddedFunction) {
			        service.serviceAddedFunction();
			    	service.serviceAddedFunction = null;
				}
				
				if(pendingPropertyUpdates[subscriptionId])
        		{
            		receivePropertyUpdate(pendingPropertyUpdates[subscriptionId]);
            		delete pendingPropertyUpdates[subscriptionId];
        		}    
			}
		}
	    receiveRenewCompleted(subscriptionId,timeout);
	};

 
 
     /**
    * Calls ReportChanged of the property to notify listeners
    * @method setPropertyChanged
    * @param {Int} subscriptionId The subscription id of the service
    * @param {String} propertyName The property name to update
    * @param {String} propertyValue The new value of the property
    */
    var setPropertyChanged = function (subscriptionId, propertyName, propertyValue) {
        var service = services[subscriptionId];
        if (service) {
            var property = service.serviceProperties[propertyName];
            if (property) {
                property.reportChanged(propertyValue);
            }
        }
    };


    /**
    * Sends a renew socket message to renew the subscription
    * @method renewSubscription
    * @param {Int} subscriptionId The subscription id of the service
    */
    var renewSubscription = function (subscriptionId) {
        var service = services[subscriptionId];
        if (service && service.SubscriptionTimer) {
            (webSocketLive) ? ws.renew(subscriptionId) : lp.renew(subscriptionId);
        }
    };
    
	/**
	* Starts the timer to renew subscriptions. 
	* The actual subscription timeout is returned by the ohnet Service.
	* subscriptionTimeoutSeconds is the suggested timeout sent to the server.
	* @method receiveRenewCompleted
	* @param {Int} subscriptionId The subscription id of the service
	* @param {Object} xmlDoc The XML to traverse
	*/
	var receiveRenewCompleted = function (subscriptionId, timeout) {
	    setSubscriptionTimeout(subscriptionId, timeout);
	    if (this.debug) {
	        console.log("receiveRenewCompleted - subscriptionId:" + subscriptionId + ' timeout:'+timeout);
	    }
	};


	/**
	* Traveres the XML object to extract the property updates
	* @method receivePropertyUpdate
	* @param {Int} subscriptionId The subscription id of the service
	* @param {Object} xmlDoc The XML to traverse
	*/
	var receivePropertyUpdate = function (xmlDoc) {
	    	var subscriptionNodes = xmlDoc.getElementsByTagNameNS("*", "SUBSCRIPTION"); // NON-IE
	    	for(var i = 0 ; i < subscriptionNodes.length; i++)
	    	{
	    		var subscriptionId = subscriptionNodes[i].getElementsByTagNameNS("*", "SID")[0].textContent; // NON-IE#
	    		if(!services[subscriptionId])
				{
					pendingPropertyUpdates[subscriptionId] = xmlDoc;
					return;	
				}
		    
		        var properties = subscriptionNodes[i].getElementsByTagNameNS("*", "property"); // NON-IE
		        if (properties) {
		        	for (var j = 0; j < properties.length; j++) {
		        		var property = properties[j].childNodes[0];
		                if (property) {
		                    setPropertyUpdate(subscriptionId, property.tagName, property.textContent);
		                    if (Debug) {
		                        console.log("receivePropertyUpdate - subscriptionId: " + subscriptionId + " name: "+ property.tagName + " value: "+property.textContent);
		                    }
		                }
		            }
		
		            for (var p = 0; p < properties.length; p++) {
		                var property = properties[p].childNodes[0];
		                if (property) {
		                    setPropertyChanged(subscriptionId, property.tagName, property.textContent);
		                }
		            }
		        }
	       }
		
	};

    
    /**
    * Socket event for when an error occurs.  Debugging purposes only.
    * @method onSocketError
    */
    var onSocketError = function () {
        webSocketLive = false;
        console.log("onSocketError");
    };

    /**
    * Socket event for when the socket is closed.  Debugging purposes only.
    * @method onSocketClose
    */
    var onSocketClose = function () {
	    webSocketLive = false;
        console.log("onSocketClose");
        stop();
		
		if(webSocketAttempts < WEBSOCKETRETRYATTEMPTS)
		{
        	setTimeout(function () { reconnect(); }, 1000);
        	webSocketAttempts ++;
        }
        else
        {
        	startLongPolling();	
        }
    };

 	
    /** 
    * Reconnects to the Web Socket Server
    * @method reconnect
    */
    var reconnect = function () {
        start({
        	startedFunction : StartedFunction,
    		port : webSocketPort,
    		debugMode : Debug,
    		subscriptionTimeoutSeconds : subscriptionTimeoutSeconds
        });
    };
    /**
    * Socket event for when the socket is opened.  Debugging purposes only.
    * @method onSocketOpen
    */
    var onSocketOpen = function () {
		webSocketLive = true;
        console.log("onSocketOpen");
        if(StartedFunction)
        	StartedFunction();
    };

   
    
  
    
    /**
    * Starts the Subscription Manager and opens a Web Socket.
    * @method start
    * @param {Object} options Contains user defined options
    */
    var start = function (options) { 
    	
    	var defaults = {
    		startedFunction : null,
    		port : null,
    		debugMode : false,
    		subscriptionTimeoutSeconds : DEFAULT_SUBSCRIPTION_TIMEOUT_SEC,
    		errorFunction : null,
    		allowWebSockets : true
    	};
    	
    	options = ohnet.util.mergeOptions(defaults,options);
    	
    	allowWebSockets = options.allowWebSockets;
    	clientId = ohnet.util.generateGUID();
        StartedFunction = options.startedFunction;
        ErrorFunction = options.errorFunction;
        Debug = options.debugMode;
        webSocketPort = options.port;
        subscriptionTimeoutSeconds = options.subscriptionTimeoutSeconds;
        
        if (Debug) {
            console.log("*** ohnet.SubscriptionManager ***");
        }
        
        if(options.port && options.port!="")
        {	
        	var websocketSupported = ("WebSocket" in window);
        	if (websocketSupported && allowWebSockets) { // NON-IE check if Websockets is supported
        		startWebSocket("ws://" + window.location.hostname + ":"+options.port+"/");
	        }
	        else {
	        	
	            startLongPolling();
	        }
        }
        else
        {
            if (Debug) {
                console.log("start/port: NULL");
            }
            
            if(options.errorFunction)
            	options.errorFunction('Connection failed.');
        }
    };
    
     /**
    * Start messaging via long polling
    * @method startLongPolling
    * @param {String} url The suggested subscription timeout value.  Overrides the default.
    */
    var startLongPolling = function () {
    	if (Debug) {
            console.log("start/startLongPolling");
        }
        
        lp = new ohnet.longpolling(clientId,nodeUdn,
    	{
    		debug:Debug,
    		subscriptionTimeoutSeconds : DEFAULT_SUBSCRIPTION_TIMEOUT_SEC,
			onReceivePropertyUpdate: receivePropertyUpdate,
			onReceiveSubscribeCompleted: receiveSubscribeCompleted,
			onReceiveRenewCompleted: receiveRenewCompleted
    	});
        
		running = true;
		if(StartedFunction)
        	StartedFunction();
   	}; 
   	
   	/**
    * Start messaging via websocket
    * @method startWebSocket
    */
    var startWebSocket = function (url) {
    
        if (Debug) {
            console.log("start/startWebSocket: " + url);
        }
        ws = new ohnet.websocket(clientId,url,
    	{
    		debug:Debug,
    		subscriptionTimeoutSeconds : DEFAULT_SUBSCRIPTION_TIMEOUT_SEC,
			onSocketError : onSocketError,
			onSocketClose : onSocketClose,
			onSocketOpen : onSocketOpen,
			onReceivePropertyUpdate: receivePropertyUpdate,
			onReceiveSubscribeCompleted: receiveSubscribeCompleted,
			onReceiveRenewCompleted: receiveRenewCompleted
    	});
        running = true;
   	}; 

 
    /**
    * Stops the Subscription Manager and removes all services
    * @method stop
    */
    var stop = function () {
    	for (var key in services) {
  			if (services.hasOwnProperty(key)) {
    			removeService(services[key]);
  			}
		}
      
        if (webSocketLive) {
            ws.close();
        }
    };
    
 	/**
    * Helper method to count services
    * @method countServices
    */
    var countServices = function () {
       var serviceCount = 0; 
       for (var key in services) {
  			if (services.hasOwnProperty(key)) {
  				serviceCount ++;
  			}
  		}
  		return serviceCount;
    };
    
    /**
    * Adds a new service to the Services collection and subscribes for property changes
    * @method addService
    * @param {Object} service The Service to be added
    * @param {Function} serviceAddedFunction The function to call once the service has been successfully added
    */
    var addService = function (service, serviceAddedFunction) {
        if (running) {
			pendingServices.push(service);
			
            if (serviceAddedFunction) {
                service.serviceAddedFunction = serviceAddedFunction;
            }
            (webSocketLive) ? ws.subscribe(service) : lp.subscribe(service,countServices()==0);
        }
        else {
            if (Debug) {
                console.log("addService/running: false");
            }
            alert("Subscription Manager is not running.  Please ensure 'ohnet.SubscriptionManager.start();' has been called prior to subscribing.");
        }
    };

    /**
    * Removes a service from the Services collection and unsubscribes
    * @method removeService
    * @param {Int} subscriptionId The subscription id of the service
    */
    var removeService = function (subscriptionId) {
        var service = services[subscriptionId];

        if (service) {
        	delete services[subscriptionId];
			(webSocketLive) ? ws.unsubscribe(subscriptionId) : lp.unsubscribe(subscriptionId,countServices()==0);
			
            if (service.SubscriptionTimer) { // Stop in-progress timers
                clearTimeout(service.SubscriptionTimer);
            }
            
        }
    };

    return {
        // Public Variables
        running: running,

        // Public Methods
        start: start,
        stop: stop,
        addService: addService,
        removeService: removeService
    };
})();

