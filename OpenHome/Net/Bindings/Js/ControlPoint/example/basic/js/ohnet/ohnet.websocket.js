
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
* Creates websocket and messages for eventing
* @namespace ohnet
* @class websocket
*/

ohnet.websocket = function (clientId,url,options) {
	
	var _this = this;
	
   	this.clientId = clientId;
   	this.socket = new WebSocket(url, "upnpevent.openhome.org");
   	
   	var defaults = {
   			debug : false,
   			subscriptionTimeoutSeconds: 1800,
    		onSocketError : null,
    		onSocketClose : null,
    		onSocketOpen : null,
    		onReceivePropertyUpdate: null,
    		onReceiveSubscribeCompleted: null,
    		onReceiveRenewCompleted: null
    };
      
    options = ohnet.util.mergeOptions(defaults,options);
    
    this.debug = options.debug;
    this.subscriptionTimeoutSeconds = options.subscriptionTimeoutSeconds;
	
	this.socket.onerror = options.onSocketError;
	this.socket.onclose = options.onSocketClose;
	this.socket.onopen = options.onSocketOpen;
	
	this.socket.onmessage = function() {
		if (_this.debug) { console.log('<< ' + event.data); }
    	_this.receiveMessage(event.data);
	};
	
	this.onReceivePropertyUpdate =  options.onReceivePropertyUpdate;
	this.onReceiveSubscribeCompleted =  options.onReceiveSubscribeCompleted;
	this.onReceiveRenewCompleted =  options.onReceiveRenewCompleted;
	
}

/**
* Subscribes a service
* @method subscribe
* @param {Object} service The service to subscribe
*/
ohnet.websocket.prototype.subscribe = function (service) {
	this.sendMessage(this.subscribeMessage(service));
}

/**
* Unsubscribes a service
* @method unsubscribe
* @param {String} subscriptionId The subscriptionId of the service to unsubscribe
*/
ohnet.websocket.prototype.unsubscribe = function (subscriptionId) {
	this.sendMessage(this.unsubscribeMessage(subscriptionId));
}

/**
* Requests to renew the subscription before it timesout
* @method renew
* @param {String} subscriptionId The subscriptionId of the service to renew
*/
ohnet.websocket.prototype.renew = function (subscriptionId) {
	this.sendMessage(this.renewMessage(subscriptionId));
}

/**
* Closes the websocket
* @method close
*/
ohnet.websocket.prototype.close = function () {
	this.socket.close()
}

/**
* Helper method to send message via websocket
* @method sendMessage
* * @param {String} message The message to send
*/
ohnet.websocket.prototype.sendMessage = function (message) {
	if (this.debug) { console.log('>> ' + message); }
	this.socket.send(message);
}

 /**
* Parses the XML message received from the ohnet Service
* @method receiveMessage
* @param {String} message The XML message
*/
ohnet.websocket.prototype.receiveMessage = function (message) {
    if (window.DOMParser) { // NON-IE
        parser = new DOMParser();
        xmlDoc = parser.parseFromString(message, "text/xml");

        var methodNode = xmlDoc.getElementsByTagNameNS("*", "METHOD"); // NON-IE
        var method = methodNode[0].textContent;

        var subscriptionIdNode = xmlDoc.getElementsByTagNameNS("*", "SID"); // NON-IE
        var subscriptionId = subscriptionIdNode[0].textContent;

        if (method == "PropertyUpdate") {
            this.onReceivePropertyUpdate(xmlDoc);
        }
        else if (method == "SubscribeCompleted") {
        	 var udnNode = xmlDoc.getElementsByTagNameNS("*", "UDN"); // NON-IE
	         var udn = udnNode[0].textContent;
	         var serviceNode = xmlDoc.getElementsByTagNameNS("*", "SERVICE"); // NON-IE
	         var service = serviceNode[0].textContent;
	         var timeoutNode = xmlDoc.getElementsByTagNameNS("*", "TIMEOUT"); // NON-IE
	         var timeout = timeoutNode[0].textContent;
             this.onReceiveSubscribeCompleted(subscriptionId,udn,service,timeout);
        }
        else if (method == "RenewCompleted") {
        	this.onReceiveRenewCompleted(subscriptionId, xmlDoc);
        }
    }
    else {
        console.log("ohnet.SubscriptionManager: Cannot parse subscription message as browser does not support it.");
    }
};



/**
* Generates the subscribe message to register the service's subscription
* @method subscribeMessage
* @param {Object} service The service interested in subscribing
* @return {String} The subscribe message to be sent to the ohnet service 
*/

ohnet.websocket.prototype.subscribeMessage = function (service) {

    var message = "<?xml verison='1.0' ?>";
    message += "<ROOT>";
    message += "<METHOD>Subscribe</METHOD>";
    message += "<CLIENTID>" + this.clientId + "</CLIENTID>";
    message += "<UDN>" + service.udn + "</UDN>";
    message += "<SERVICE>" + service.serviceName + "</SERVICE>";
    message += "<NT>upnp:event</NT>";
    message += "<TIMEOUT>" + this.subscriptionTimeoutSeconds + "</TIMEOUT>";
    message += "</ROOT>";
    return message;
};

/**
* Generates the Unsubscribe message to unregister the service's subscription
* @method unsubscribeMessage
* @param {Int} subscriptionId The subscription id of the service interested in unsubscribing
* @return {String} The unsubscribe message to be sent to the ohnet service 
*/

ohnet.websocket.prototype.unsubscribeMessage = function (subscriptionId) {

    var message = "<?xml verison='1.0' ?>";
    message += "<ROOT>";
    message += "<METHOD>Unsubscribe</METHOD>";
    message += "<SID>" + subscriptionId + "</SID>";
    message += "<CLIENTID>" + this.clientId + "</SID>";
    message += "</ROOT>";
    return message;
};


/**
* Generates the Renew message to renew the service's subscription
* @method renewMessage
* @param {Int} subscriptionId The subscription id of the service interested in renewing the subscription
* @return {String} The renew message to be sent to the ohnet service 
*/
ohnet.websocket.prototype.renewMessage = function (subscriptionId) {

    var message = "<?xml verison='1.0' ?>";
    message += "<ROOT>";
    message += "<METHOD>Renew</METHOD>";
    message += "<SID>" + subscriptionId + "</SID>";
    message += "<TIMEOUT>" + this.subscriptionTimeoutSeconds + "</TIMEOUT>";
    message += "</ROOT>";
    return message;
};

/**
* Generates the Get property Updates message used for long polling
* @method getPropertyUpdatesMessage
* @return {String} The get property update message to be sent to the ohnet service 
*/
ohnet.websocket.prototype.getPropertyUpdatesMessage = function () {

    var message = "<?xml verison='1.0' ?>";
    message += "<ROOT>";
    message += "<CLIENTID>" + this.clientId + "</CLIENTID>";
    message += "</ROOT>";
    return message;
};

