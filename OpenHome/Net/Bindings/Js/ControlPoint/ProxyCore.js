/**
* The OhNet object is the single global object used by OhNet Services to
* facilitate actions and subscriptions. 
* @module OhNet
* @title OhNet
*/

if (typeof OhNet == "undefined" || !OhNet) {
    /**
    * The OhNet global namespace object.  If OhNet is already defined, the
    * existing OhNet object will not be overwritten so that defined
    * namespaces are preserved.
    * @class OhNet
    * @static
    */
    var OhNet = {};
}

/**
* Manages the subscriptions to the OhNet Services.
* Subscribed services are notified of property state changes.
* @namespace OhNet
* @class SubscriptionManager
* @static
*/
OhNet.SubscriptionManager = (function () {

    // Constants 
    var DEFAULT_SUBSCRIPTION_TIMEOUT_SEC = 1800; // The default suggested timeout in seconds for each subscription.
    var WEBSOCKETRETRYATTEMPTS = 1; // The number if retries for websockets before falling back to long polling (does not include initial attempt).
    var RENEW_TRIGGER = 0.7; // The multiplier in which to send the renewal message. (Send renew message every RENEW_TRIGGER * DEFAULT_SUBSCRIPTION_TIMEOUT_SEC)
    var DEBUG = false; // A flag to enable debugging messages written to console
 	var ALLOWWEBSOCKET = true; // A flag to force the subscription manager to always use long polling
 	
    // Private Variables
    var services = []; // Collection of OhNet services
    var websocket = null; // HTML 5 web socket object to handle property state events
    var subscriptionCounter = -1; // A unique identifier for each subscription (zero-based).
    var SubscriptionTimeoutSeconds = -1; // The suggested timeout in seconds for each subscription.
	var clientId = '';
	
    var StartedFunction;
    var ErrorFunction;
    var Debug;
    var webSocketPort;
    var webSocketAttempts = 0;
    var webSocketLive = false;
    var longPollingUrl = '';
   
    
    var pendingServices = [];
	var pendingPropertyUpdates = {};
    // Public Variables
    var running = false; // A flag to state if the Subscription Manager is running


    // Functions

    /**
    * Generates the subscribe message to register the service's subscription
    * @method subscribeMessage
    * @param {Object} service The service interested in subscribing
    * @return {String} The subscribe message to be sent to the OhNet service 
    */
    var subscribeMessage = function (service) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Subscribe</METHOD>";
        message += "<CLIENTID>" + clientId + "</CLIENTID>";
        message += "<UDN>" + service.udn + "</UDN>";
        message += "<SERVICE>" + service.serviceName + "</SERVICE>";
        message += "<NT>upnp:event</NT>";
        message += "<TIMEOUT>" + subscriptionTimeoutSeconds + "</TIMEOUT>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log(">> subscribeMessage/message: " + message);
        }
        return message;
    };


    /**
    * Generates the Unsubscribe message to unregister the service's subscription
    * @method unsubscribeMessage
    * @param {Int} subscriptionId The subscription id of the service interested in unsubscribing
    * @return {String} The unsubscribe message to be sent to the OhNet service 
    */
    var unsubscribeMessage = function (subscriptionId) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Unsubscribe</METHOD>";
        message += "<SID>" + subscriptionId + "</SID>";
        message += "<CLIENTID>" + clientId + "</SID>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log(">> unsubscribeMessage/message: " + message);
        }

        return message;
    };


    /**
    * Generates the Renew message to renew the service's subscription
    * @method renewMessage
    * @param {Int} subscriptionId The subscription id of the service interested in renewing the subscription
    * @return {String} The renew message to be sent to the OhNet service 
    */
    var renewMessage = function (subscriptionId) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Renew</METHOD>";
        message += "<SID>" + subscriptionId + "</SID>";
        message += "<TIMEOUT>" + subscriptionTimeoutSeconds + "</TIMEOUT>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log(">> renewMessage/message: " + message);
        }

        return message;
    };
    
    /**
    * Generates the Get property Updates message used for long polling
    * @method getPropertyUpdatesMessage
    * @return {String} The get property update message to be sent to the OhNet service 
    */
    var getPropertyUpdatesMessage = function () {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<CLIENTID>" + clientId + "</CLIENTID>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log(">> getPropertyUpdatesMessage/message: " + message);
        }

        return message;
    };


    /**
    * Starts the timer to renew subscriptions. 
    * The actual subscription timeout is returned by the OhNet Service. 
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

            if (DEBUG) {
                console.log("setSubscriptionTimeout/actualSubscriptionTimeoutMs:" + actualSubscriptionTimeoutMs);
            }
        }
        else {
            if (DEBUG) {
                console.log("setSubscriptionTimeout/service: NULL");
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
                if (DEBUG) {
                    console.log("setPropertyUpdate/aSubscriptionId: " + subscriptionId);
                    console.log("setPropertyUpdate/propertyName: " + propertyName);
                    console.log("setPropertyUpdate/propertyValue: " + propertyValue);
                }
            }
            else {
                if (DEBUG) {
                    console.log("setPropertyUpdate/service: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("setPropertyUpdate/service: NULL");
            }
        }
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
                if (DEBUG) {
                    console.log("setPropertyChanged/aSubscriptionId: " + subscriptionId);
                    console.log("setPropertyChanged/propertyName: " + propertyName);
                    console.log("setPropertyChanged/propertyValue: " + propertyValue);
                }
            }
            else {
                if (DEBUG) {
                    console.log("setPropertyChanged/service: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("setPropertyChanged/service: NULL");
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
        if (service) {
            if (service.SubscriptionTimer) {
                sendMessage(renewMessage(subscriptionId));
                if (DEBUG) {
                    console.log("renewSubscription/subscriptionId: " + subscriptionId);
                }
            }
            else {
                if (DEBUG) {
                    console.log("renewSubscription/service.SubscriptionTimer: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("renewSubscription/service: NULL");
            }
        }
    };

    /**
    * Parses the XML message received from the OhNet Service
    * @method receiveMessage
    * @param {String} message The XML message
    */
    var receiveMessage = function (message) {
        if (window.DOMParser) { // NON-IE
            parser = new DOMParser();
            xmlDoc = parser.parseFromString(message, "text/xml");

            var methodNode = xmlDoc.getElementsByTagNameNS("*", "METHOD"); // NON-IE
            var method = methodNode[0].textContent;

            var subscriptionIdNode = xmlDoc.getElementsByTagNameNS("*", "SID"); // NON-IE
            var subscriptionId = subscriptionIdNode[0].textContent;

            if (DEBUG) {
                console.log("<< receiveMessage/method: " + method);
            }

            if (method == "PropertyUpdate") {
                receivePropertyUpdate(xmlDoc);
                if(!webSocketLive && longPollingUrl!= '')
                {
                	sendMessage(getPropertyUpdatesMessage());
                }
            }
            else if (method == "SubscribeCompleted") {
            	var udnNode = xmlDoc.getElementsByTagNameNS("*", "UDN"); // NON-IE
            	var udn = udnNode[0].textContent;
            	var serviceNode = xmlDoc.getElementsByTagNameNS("*", "SERVICE"); // NON-IE
            	var service = serviceNode[0].textContent;
                receiveSubscribeCompleted(subscriptionId,udn,service, xmlDoc);
                if(pendingPropertyUpdates[subscriptionId])
                {
                	receivePropertyUpdate(subscriptionId, pendingPropertyServices[subscriptionId]);
                }
                
                if(!webSocketLive && longPollingUrl!= '')
                {
                	sendMessage(getPropertyUpdatesMessage());
                }
            }
            else if (method == "RenewCompleted") {
            	receiveRenewCompleted(subscriptionId, xmlDoc);
            }
        }
        else {
            alert("OhNet.SubscriptionManager: Cannot parse subscription message as browser does not support it.");
            if (DEBUG) {
                console.log("receiveMessage/window.DOMParser: NULL");
            }
        }
    };


    /**
    * Traveres the XML object to extract the property updates
    * @method receivePropertyUpdate
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Object} xmlDoc The XML to traverse
    */
    var receivePropertyUpdate = function (xmlDoc) {
    	try
    	{
	    	var subscriptionNodes = xmlDoc.getElementsByTagNameNS("*", "SUBSCRIPTION"); // NON-IE
	    	for(var i = 0 , count = subscriptionNodes.length;  i < count; i++)
	    	{
	    		var subscriptionId = subscriptionNodes[i].getElementsByTagNameNS("*", "SID")[0].textContent; // NON-IE
	    		
		    	if(!services[subscriptionId])
				{
					pendingPropertyUpdates[subscriptionId] = xmlDoc;
					return;	
				}
		    	
		        var properties = xmlDoc.getElementsByTagNameNS("*", "property"); // NON-IE
		        if (properties) {
		            for (var i = 0, count = properties.length; i < count; i++) {
		                var property = properties[i].childNodes[0];
		                if (property) {
		                    setPropertyUpdate(subscriptionId, property.tagName, property.textContent);
		                    if (DEBUG) {
		                        console.log("setPropertyUpdate");
		                        console.log("receivePropertyUpdate/subscriptionId: " + subscriptionId);
		                        console.log("receivePropertyUpdate/property.tagName: " + property.tagName);
		                        console.log("receivePropertyUpdate/property.textContent: " + property.textContent);
		                    }
		                }
		                else {
		                    if (DEBUG) {
		                        console.log("receivePropertyUpdate/property: NULL");
		                    }
		                }
		            }
		
		            for (var i = 0, count = properties.length; i < count; i++) {
		                var property = properties[i].childNodes[0];
		                if (property) {
		                    setPropertyChanged(subscriptionId, property.tagName, property.textContent);
		                    if (DEBUG)
		                        console.log("setPropertyChanged");
		                }
		                else {
		                    if (DEBUG) {
		                        console.log("receivePropertyUpdate/property: NULL");
		                    }
		                }
		            }
		        }
		        else {
		            if (DEBUG) {
		                console.log("receivePropertyUpdate/properties: NULL");
		            }
		        }
	       }
		}
		catch(e)
		{
			console.log(e);
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
    var receiveSubscribeCompleted = function (subscriptionId,udn,service, xmlDoc) {
		
		if (DEBUG) {
			console.log("receiveSubscribeCompleted/subscriptionId: "+subscriptionId); 
            console.log("receiveSubscribeCompleted/udn: "+udn);
            console.log("receiveSubscribeCompleted/service: "+service);
            console.log("receiveSubscribeCompleted/pendingServices.length: "+pendingServices.length);
        }
        
        for(var i = 0 ; i < pendingServices.length; i++)
        {
        	var pendingService = pendingServices[i];
        	if(pendingService.udn == udn && pendingService.serviceName == service)
        	{
        		services[subscriptionId] = pendingService;
        		pendingServices.splice(i,1);
        		var service = services[subscriptionId];
                if (service.serviceAddedFunction) {
                    service.serviceAddedFunction();
                    service.serviceAddedFunction = null;
                }
        		if (DEBUG) {
        			console.log("receiveSubscribeCompleted/Removing pending service");
            		console.log("receiveSubscribeCompleted/pendingServices.length: "+pendingServices.length);
        		}
        		break;
        	}
        }        
        receiveRenewCompleted(subscriptionId,xmlDoc);
    };
    
    
	/**
    * Starts the timer to renew subscriptions. 
    * The actual subscription timeout is returned by the OhNet Service.
    * subscriptionTimeoutSeconds is the suggested timeout sent to the server.
    * @method receiveRenewCompleted
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Object} xmlDoc The XML to traverse
    */
    var receiveRenewCompleted = function (subscriptionId, xmlDoc) {
		
		if (DEBUG) {
			console.log("receiveRenewCompleted/subscriptionId: "+subscriptionId); 
        }
                
        var timeoutNode = xmlDoc.getElementsByTagNameNS("*", "TIMEOUT");
        if (timeoutNode) {
            var timeout = timeoutNode[0].textContent;
            if (timeout) {
                setSubscriptionTimeout(subscriptionId, timeout);
                if (DEBUG) {
                    console.log("receiveRenewCompleted/subscriptionId: " + subscriptionId);
                    console.log("receiveRenewCompleted/timeout: " + timeout);
                }
            }
            else {
                if (DEBUG) {
                    console.log("receiveRenewCompleted/timeoutNode: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("receiveSubscribeCompleted/timeouts: NULL");
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
        	startLongPolling(websocket.URL.replace('ws://','http://'));	
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
    		subscriptionTimeoutSeconds : SubscriptionTimeoutSeconds
        });
    };
    /**
    * Socket event for when the socket is opened.  Debugging purposes only.
    * @method onSocketOpen
    */
    var onSocketOpen = function () {
		webSocketLive = true;
        console.log("onSocketOpen");
        StartedFunction();
    };

    /**
    * Socket event for when a message is received.
    * @method onSocketMessage
    * @param {Object} event The data received
    */
    var onSocketMessage = function (event) {
        receiveMessage(event.data);

        if (DEBUG) {
            console.log("onSocketMessage/event.data: " + event.data);
        }

    };
    
    /**
    * A helper method to generate a GUID as a client id
    * @method generateGUID
    */
    var generateGUID = function () {

    	var guid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
	        var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
	        return v.toString(16);;
	    });
	    if (DEBUG) {
        	console.log("generateGUID/guid: " + guid);
    	}
    	return guid;
    };
    
    /**
    * A helper method to merge options
    * @method extend
    * @param {Object} defaults Collection that contains default options
    * @param {Object} options Collection that contains user defined options
    */
     var mergeOptions = function (defaults,options) {
    	var newoptions = {};
    	for (var attrname in defaults) { newoptions[attrname] = defaults[attrname]; }
    	for (var attrname in options) { newoptions[attrname] = options[attrname]; }
    	return newoptions;
    };

    
    
    /**
    * Send a message based either through websockets or long polling
    * @method sendMessage
    * @param {String} message The message to send
    */
    var sendMessage = function (message) {
		if(webSocketLive)
		{
			websocket.send(message);
		}
		else // Long Polling
		{
			var request = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');
		    request.onreadystatechange = function () {
		        if (request.readyState != 4)
		            return;
		        if (request.status == 200) {
		        	if (DEBUG) {
            			console.log("sendMessage/LongPolling/responseText: " + request.responseText);
        			}
		            receiveMessage(request.responseText);  
		        }
		    };
		    request.open('POST', longPollingUrl, true);
		    request.timeout = 60000;
		    request.send(message);
		}
    	
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
    	
    	options = mergeOptions(defaults,options);
    	
    	ALLOWWEBSOCKET = options.allowWebSockets;
    	clientId = generateGUID();
        StartedFunction = options.startedFunction;
        ErrorFunction = options.errorFunction;
        Debug = options.debugMode;
        webSocketPort = options.port;
        subscriptionTimeoutSeconds = options.subscriptionTimeoutSeconds;
        
        console.log(options);
        if (Debug) {
            DEBUG = options.debugMode;
            console.log("*** OhNet.SubscriptionManager ***");
        }
        
        if(options.port && options.port!="")
        {	
        	var websocketSupported = ("WebSocket" in window);
        	if (websocketSupported && ALLOWWEBSOCKET) { // NON-IE check if Websockets is supported
        		startWebSocket("ws://" + window.location.hostname + ":"+options.port+"/");
	        }
	        else {
	        	
	            startLongPolling("http://" + window.location.hostname + ":"+options.port+"/");
	        }
        }
        else
        {
            if (DEBUG) {
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
    var startLongPolling = function (url) {
    	if (DEBUG) {
            console.log("startLongPolling: Starting");
        }
        longPollingUrl = url;
        running = true;
        StartedFunction();
   	}; 
   	
   	/**
    * Start messaging via websocket
    * @method startWebSocket
    */
    var startWebSocket = function (url) {
    
        if (DEBUG) {
            console.log("start/websocketServerLocation: " + url);
        }
        websocket = new WebSocket(url, "upnpevent.openhome.org");
      
        websocket.onmessage = onSocketMessage;
        websocket.onerror = onSocketError;
        websocket.onclose = onSocketClose;
        websocket.onopen = onSocketOpen;
    	if (DEBUG) {
            console.log("startWebSocket: Starting");
        }
        running = true;
   	}; 

 
    /**
    * Stops the Subscription Manager and removes all services
    * @method stop
    */
    var stop = function () {
        for (var i = services.length - 1; i > -1; i--) {
            var service = services[i];
            if (service) {

                if (DEBUG) {
                    console.log("stop/service.subscriptionId: " + service.subscriptionId);
                }

                removeService(service.subscriptionId);
            }
            else {
                if (DEBUG) {
                    console.log("stop/service: NULL");
                }
            }
        }
        if (websocket) {
            websocket.close();
        }
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
            sendMessage(subscribeMessage(service))
            if (DEBUG) {
                console.log("addService/service.subscriptionId : " + service.subscriptionId);
            }
        }
        else {
            if (DEBUG) {
                console.log("addService/running: false");
            }
            alert("Subscription Manager is not running.  Please ensure 'OhNet.SubscriptionManager.start();' has been called prior to subscribing.");
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

            sendMessage(unsubscribeMessage(subscriptionId));

            if (service.SubscriptionTimer) { // Stop in-progress timers
                clearTimeout(service.SubscriptionTimer);
            }
            delete services[subscriptionId];

            if (DEBUG) {
                console.log("removeService\services[aSubscriptionId] (Should be null): " + services[subscriptionId]);
            }
        }
        else {
            if (DEBUG) {
                console.log("removeService\service: NULL");
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




/**
* A Service Property that can be monitored of state changes
* @namespace OhNet
* @class ServiceProperty
*/
OhNet.ServiceProperty = function (name, type) {
    this.name = name; // The name of the property
    this.type = type;
    this.value = null; // The value of the property
    this.listeners = []; // A collection of listeners to notify of property value changes
}

/**
* Sets the value of the property
* @method setValue
* @param {String | Int | Boolean} value The new value for the property
*/
OhNet.ServiceProperty.prototype.setValue = function (value) {
    if (this.value != value) {

        switch (this.type) {

            case "int":
                {
                    this.value = OhNet.SoapRequest.readIntParameter(value);
                    break;
                }
            case "string":
                {
                    this.value = OhNet.SoapRequest.readStringParameter(value);
                    break;
                }
            case "bool":
                {
                    this.value = OhNet.SoapRequest.readBoolParameter(value);
                    break;
                }
            case "binary":
                {
                    this.value = OhNet.SoapRequest.readBinaryParameter(value);
                    break;
                }
            default:
                {
                    throw "Invalid Property Type: '" + this.type + "'";
                }
        }

       
    }
}

/**
* Notifies all listeners of its value change and calls the event handler
* @method reportChanged
* @param {String | Int | Boolean} value The new value for the property
*/
OhNet.ServiceProperty.prototype.reportChanged = function (value) {
    for (var i = this.listeners.length - 1; i > -1; i--) {
        try {
            this.listeners[i].call(this, value);

        } catch (e) {
            console.log("reportChanged: " + e);
        }
    }
}

/**
* Adds a new event handler function to the listeners for the property
* @method addListener
* @param {Function} listener The event handler function to execute when the property value changes
*/
OhNet.ServiceProperty.prototype.addListener = function (listener) {
    this.listeners[this.listeners.length] = listener;
}




/**
* A wrapper for sending and receiving soap messages via jQuery ajax
* @namespace OhNet
* @class SoapRequest
*/

OhNet.SoapRequest = function (action, url, domain, type, version) {
    this.action = action; // The action to invoke
    this.url = url; // The soap web service url
    this.type = type;
    this.version = version;
    this.domain = domain;
    this.envelope = ""; // The soap envelope
    this.writeEnvelopeStart(action);
}

/**
* Builds the start of the soap message
* @method writeEnvelopeStart
*/
OhNet.SoapRequest.prototype.writeEnvelopeStart = function () {
    var envelopeStart = '<?xml version="1.0"?>' +
        '<s:Envelope xmlns:s="http://schemas.xmlsoap.org/soap/envelope/">' +
        '<s:Body s:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"><u:';

    this.envelope += envelopeStart;
    this.envelope += this.action;
    this.envelope += ' xmlns:u="urn:';
    this.envelope += this.domain;
    this.envelope += ':service:';
    this.envelope += this.type;
    this.envelope += ':';
    this.envelope += this.version;
    this.envelope += '">';
}


/**
* Builds the end of the soap message
* @method writeEnvelopeEnd
*/
OhNet.SoapRequest.prototype.writeEnvelopeEnd = function () {
    this.envelope += "</u:";
    this.envelope += this.action;
    this.envelope += "></s:Body></s:Envelope>";
}


/**
* Builds the action of the soap message
* @method getSoapAction
*/
OhNet.SoapRequest.prototype.getSoapAction = function () {
    var soapAction = 'urn:';
    soapAction += this.domain;
    soapAction += ':service:';
    soapAction += this.type;
    soapAction += ':';
    soapAction += this.version;
    soapAction += '#';
    soapAction += this.action;
    return soapAction;
}


/**
* Executes the ajax request
* @method send
* @param {Function} successFunction The function to execute once the ajax request returns
* @param {Function} errorFunction The function to execute if an error occurs in the ajax request
*/
OhNet.SoapRequest.prototype.send = function (successFunction, errorFunction) {
    var _this = this;
    this.writeEnvelopeEnd();
    return this.createAjaxRequest(
		function (transport) {
		    if (transport.responseXML.getElementsByTagName("faultcode").length > 0) {
		        errorFunction(_this.getTransportErrorMessage(transport), transport);
		    } else {

		        var outParameters = transport.responseXML.getElementsByTagNameNS("*", _this.action + "Response")[0].childNodes;

		        // Parse the output
		        var result = {};
		        for (var i = 0, il = outParameters.length; i < il; i++) {
		            var nodeValue = "";
		            // one result is expected
		            var children = outParameters[i].childNodes;
		            if (children.length > 0) {
		                nodeValue = children[0].nodeValue;
		            }
		            result[outParameters[i].nodeName] = (nodeValue != "" ? nodeValue : null);
		        }
		        successFunction(result);

		    }
		},
		function (transport) {
		    if (errorFunction) {
		        errorFunction(_this.getTransportErrorMessage(transport), transport);
		    }
		    else {
		        defaultErrorFunction(XMLHttpRequest, errorType, errorThrown);
		    }
		}
	);
}



/**
* A wrapper of the ajax request
* @method createAjaxRequest
* @param {Function} successFunction The function to execute once the ajax request returns
* @param {Function} errorFunction The function to execute if an error occurs in the ajax request
*/
OhNet.SoapRequest.prototype.createAjaxRequest = function (successFunction, errorFunction) {

    var request = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');

    request.onreadystatechange = function () {
        if (request.readyState != 4)
            return;
        if (request.status == 200) {
            if (successFunction)
                successFunction(request);
        }
        else {
            if (errorFunction)
                errorFunction(request);
        }
    };

    request.open('POST', this.url, true);
    request.setRequestHeader('SOAPAction', this.getSoapAction());
    request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    request.send(this.envelope);
}

/**
* Provides a default error handler to output the error to console
* @method defaultErrorFunction
* @param {Object} XMLHttpRequest The XMLHTTPRequest
* @param {String} textStatus The error type
* @param {Object} errorThrown The exception object if applicable
*/
OhNet.SoapRequest.prototype.defaultErrorFunction = function (XMLHttpRequest, textStatus, errorThrown) {
    console.log("defaultErrorFunction/XMLHttpRequest: " + XMLHttpRequest);
    console.log("defaultErrorFunction/textStatus: " + textStatus);
    console.log("defaultErrorFunction/errorThrown: " + errorThrown);
}


/**
* Parses the SOAP error message into a readable string
* @method getTransportErrorMessage
* @param {Object} transport The XMLHttpRequest object
* @return {String} A readable error message
*/
OhNet.SoapRequest.prototype.getTransportErrorMessage = function (transport) {
    var errorString = "Error:";
    try {
        errorString += "\nstatus: " + transport.statusText;
    } catch (e) { }
    if (transport && transport.responseXML) {
        if (transport.responseXML.getElementsByTagName("faultcode").length) {
            errorString += "\nfaultcode: " + transport.responseXML.getElementsByTagName("faultcode")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("faultstring").length) {
            errorString += "\nfaultstring: " + transport.responseXML.getElementsByTagName("faultstring")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("errorCode").length) {
            errorString += "\nerrorCode: " + transport.responseXML.getElementsByTagName("errorCode")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("errorDescription").length) {
            errorString += "\nerrorDescription: " + transport.responseXML.getElementsByTagName("errorDescription")[0].childNodes[0].nodeValue;
        }
    }
    return errorString;
}


/**
* Helper to Read an Int
* @method readIntParameter
* @param {String} value The value to be read as an Integer
* @static
* @return {Int} The integer value
*/
OhNet.SoapRequest.readIntParameter = function (value) {
    return value * 1;
}

/**
* Helper to Read an Bool
* @method readBoolParameter
* @param {String} value The value to be read as a Boolean
* @static
* @return {Boolean} The boolean value
*/
OhNet.SoapRequest.readBoolParameter = function (value) {
    return (value == "1" || value == "true" || value == "yes") ? true : false;
}

/**
* Helper to Read a String
* @method readStringParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The string value
*/
OhNet.SoapRequest.readStringParameter = function (value) {
    return value;
}

/**
* Helper to Read a Binary
* @method readBinaryParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The binary value converted from base64
*/
OhNet.SoapRequest.readBinaryParameter = function (value) {
    return atob(value);
}

/**
* Helper to write an Integer into a xml tag
* @method writeIntParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
OhNet.SoapRequest.prototype.writeIntParameter = function (tagName, value) {
    this.writeParameter(tagName, "" + (value ? value : "0"));
}

/**
* Helper to write a Boolean into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
OhNet.SoapRequest.prototype.writeBoolParameter = function (tagName, value) {
    this.writeParameter(tagName, value ? "1" : "0");
}

/**
* Helper to write a String into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
OhNet.SoapRequest.prototype.writeStringParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? value : ""));
}

/**
* Helper to write Binary into a xml tag
* @method writeBinaryParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
OhNet.SoapRequest.prototype.writeBinaryParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? btoa(value) : ""));
}


/**
* Helper to format the tag and value into a xml tag and insert into the SOAP enveloper
* @method writeParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
OhNet.SoapRequest.prototype.writeParameter = function (tagName, value) {
    this.envelope += "<" + tagName + ">" + value.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;") + "</" + tagName + ">";
}



