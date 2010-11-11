 

/**
 * Proxy for linn.co.uk:MediaTime:1
 */

var ServiceMediaTime = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-MediaTime-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "MediaTime";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-MediaTime-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Seconds"] = new ServiceVariable("Seconds");
}


ServiceMediaTime.prototype.Seconds_Changed = function (aStateChangedFunction) {
    this.Variables().Seconds.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceMediaTime.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceMediaTime.prototype.Variables = function(){
	return this.iVariables;
}

ServiceMediaTime.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceMediaTime.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceMediaTime.prototype.Udn = function () {
    return this.iUdn;
}

ServiceMediaTime.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceMediaTime.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceMediaTime.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceMediaTime.prototype.Seconds = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Seconds", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSeconds"] = SoapRequest.ReadIntParameter(result["aSeconds"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



