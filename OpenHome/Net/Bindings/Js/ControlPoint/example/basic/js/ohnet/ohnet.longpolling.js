
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
	this.pollingStarted = false;
	var defaults = {
   			debug : false,
   			subscriptionTimeoutSeconds: 1800,
    		onReceivePropertyUpdate: null,
    		onReceiveSubscribeCompleted: null,
    		onReceiveRenewCompleted: null,
    		onReceiveError : null,
    		onReceiveSuccess : null
    };
    
    options = ohnet.util.mergeOptions(defaults,options);
    
    this.debug = options.debug;
    this.subscriptionTimeoutSeconds = options.subscriptionTimeoutSeconds;
    
    this.onReceivePropertyUpdate =  options.onReceivePropertyUpdate;
	this.onReceiveSubscribeCompleted =  options.onReceiveSubscribeCompleted;
	this.onReceiveRenewCompleted =  options.onReceiveRenewCompleted;
	this.onReceiveError =  options.onReceiveError;
	this.onReceiveSuccess =  options.onReceiveSuccess;
}


/**
* Subscribes a service
* @method subscribe
* @param {Object} service The service to subscribe
* @param {Int} serviceCount The number of services
*/
ohnet.longpolling.prototype.subscribe = function (service,firstSubscription) {
	var _this = this;
	this.pollingStarted = false;
	if (this.debug) { console.log('>> Subscribe' + ' : No Services: ' + firstSubscription); }
	var srv = service;
	this.proxy.Subscribe(this.clientId,service.udn,service.serviceName,this.subscriptionTimeoutSeconds,
		function(result)
		{
			_this.onReceiveSubscribeCompleted(result.Sid,srv.udn,srv.serviceName,result.Duration);
			if(firstSubscription && !_this.pollingStarted)
			{
				_this.pollingStarted = true;
				_this.propertyUpdate();
				if (_this.debug)
				{
					console.log('>> First Subscription - start polling');
				} 
			}
		},
		function()
		{
			if (_this.onReceiveError) { _this.onReceiveError(); }
		}
	);
}

/**
* Unsubscribes a service
* @method unsubscribe
* @param {String} subscriptionId The subscriptionId of the service to unsubscribe
*/
ohnet.longpolling.prototype.unsubscribe = function (subscriptionId,noSubscriptions) {
	if (this.debug) { console.log('>> Unsubscribe: '+subscriptionId); }
	this.proxy.Unsubscribe(subscriptionId);
	if(noSubscriptions && this.pollingStarted)
	{
		this.pollingStarted = false;
	}
}

/**
* Requests to renew the subscription before it timesout
* @method renew
* @param {String} subscriptionId The subscriptionId of the service to renew
*/
ohnet.longpolling.prototype.renew = function (subscriptionId) {
	var _this = this;
	if (this.debug) { console.log('>> Renew'); }
	this.proxy.Renew(subscriptionId,this.subscriptionTimeoutSeconds,function(result) {
		_this.onReceiveRenewCompleted(subscriptionId, result.Duration);
	},
	function()
	{
		if (_this.onReceiveError) { _this.onReceiveError(); }
	}
	);
}

/**
* Polling method to get any updates for properties.  Once it returns, another request is sent.
* @method propertyUpdate
*/
ohnet.longpolling.prototype.propertyUpdate = function () {
	var _this = this;
	if (this.debug) { console.log('>> Property Update'); }
	if(this.pollingStarted)
	{
		if (this.debug) { console.log('>> GetPropertyUpdates'); }
		this.proxy.GetPropertyUpdates(this.clientId, function(results) {
            if (_this.debug) { console.log('<< GetPropertyUpdates'); }
            if (_this.onReceiveSuccess) { _this.onReceiveSuccess(); }
			if (window.DOMParser) { // NON-IE
	            var parser = new DOMParser();
	            var xmlDoc = parser.parseFromString(results.Updates, "text/xml");
	          	_this.onReceivePropertyUpdate(xmlDoc);
			}
			if(_this.pollingStarted)
			{
				setTimeout(function() { _this.propertyUpdate(); },10); // hack to stop safari from displaying loading cursor
			}
		},
		function()
		{
			if (_this.debug) { console.log('Long poll failed, retrying...'); }
			if (_this.onReceiveError) { _this.onReceiveError(); }
			if(_this.pollingStarted)
			{
				setTimeout(function() { _this.propertyUpdate(); },10); // hack to stop safari from displaying loading cursor
			}
		});
	}
}