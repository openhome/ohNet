
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
* Creates long polling connection and messages for eventing
* @namespace ohnet
* @class longpolling
*/

ohnet.longpolling = function (clientId,nodeUdn,options) {
	this.clientId = clientId;
	this.proxy =  new CpProxyOpenhomeOrgSubscriptionLongPoll1(nodeUdn);
	
	var defaults = {
   			debug : false,
   			subscriptionTimeoutSeconds: 1800,
    		onReceivePropertyUpdate: null,
    		onReceiveSubscribeCompleted: null,
    		onReceiveRenewCompleted: null
    };
    
    options = ohnet.util.mergeOptions(defaults,options);
    
    this.debug = options.debug;
    this.subscriptionTimeoutSeconds = options.subscriptionTimeoutSeconds;
    
    this.onReceivePropertyUpdate =  options.onReceivePropertyUpdate;
	this.onReceiveSubscribeCompleted =  options.onReceiveSubscribeCompleted;
	this.onReceiveRenewCompleted =  options.onReceiveRenewCompleted;
}


/**
* Subscribes a service
* @method subscribe
* @param {Object} service The service to subscribe
*/
ohnet.longpolling.prototype.subscribe = function (service) {
	var _this = this;
	if (this.debug) { console.log('>> Subscribe'); }
	var srv = service;
	this.proxy.Subscribe(this.clientId,service.udn,service.serviceName,this.subscriptionTimeoutSeconds,
		function(result)
		{
			_this.onReceiveSubscribeCompleted(result.Sid,srv.udn,srv.serviceName,result.Duration);
			_this.propertyUpdate();
		}
	);
}

/**
* Unsubscribes a service
* @method unsubscribe
* @param {String} subscriptionId The subscriptionId of the service to unsubscribe
*/
ohnet.longpolling.prototype.unsubscribe = function (subscriptionId) {
	if (this.debug) { console.log('>> Unsubscribe'); }
	this.proxy.Unsubscribe(subscriptionId);
}

/**
* Requests to renew the subscription before it timesout
* @method renew
* @param {String} subscriptionId The subscriptionId of the service to renew
*/
ohnet.longpolling.prototype.renew = function (subscriptionId) {
	if (this.debug) { console.log('>> Renew'); }
	this.proxy.Renew(subscriptionId);
}

/**
* Polling method to get any updates for properties.  Once it returns, another request is sent.
* @method propertyUpdate
*/
ohnet.longpolling.prototype.propertyUpdate = function () {
	var _this = this;
	if (this.debug) { console.log('>> Property Update'); }
	
	this.proxy.GetPropertyUpdates(this.clientId, function(results) {
		if (window.DOMParser) { // NON-IE
            var parser = new DOMParser();
            var xmlDoc = parser.parseFromString(results.Updates, "text/xml");
          	_this.onReceivePropertyUpdate(xmlDoc);
		}
		_this.propertyUpdate();
	});
}