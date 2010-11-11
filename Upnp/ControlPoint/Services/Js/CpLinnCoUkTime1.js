 

/**
 * Proxy for linn.co.uk:Time:1
 */

var ServiceTime = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Time-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Time";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Time-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["TrackCount"] = new ServiceVariable("TrackCount");
		this.iVariables["Duration"] = new ServiceVariable("Duration");
		this.iVariables["Seconds"] = new ServiceVariable("Seconds");
}


ServiceTime.prototype.TrackCount_Changed = function (aStateChangedFunction) {
    this.Variables().TrackCount.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTime.prototype.Duration_Changed = function (aStateChangedFunction) {
    this.Variables().Duration.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTime.prototype.Seconds_Changed = function (aStateChangedFunction) {
    this.Variables().Seconds.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceTime.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceTime.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTime.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceTime.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceTime.prototype.Udn = function () {
    return this.iUdn;
}

ServiceTime.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceTime.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceTime.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceTime.prototype.Time = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Time", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTrackCount"] = SoapRequest.ReadIntParameter(result["aTrackCount"]);	
		result["aDuration"] = SoapRequest.ReadIntParameter(result["aDuration"]);	
		result["aSeconds"] = SoapRequest.ReadIntParameter(result["aSeconds"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



