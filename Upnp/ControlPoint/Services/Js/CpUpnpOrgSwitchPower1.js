 

/**
 * Proxy for upnp.org:SwitchPower:1
 */

var ServiceSwitchPower = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-SwitchPower-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "SwitchPower";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-SwitchPower-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Target"] = new ServiceVariable("Target");
		this.iVariables["Status"] = new ServiceVariable("Status");
}


ServiceSwitchPower.prototype.Target_Changed = function (aStateChangedFunction) {
    this.Variables().Target.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceSwitchPower.prototype.Status_Changed = function (aStateChangedFunction) {
    this.Variables().Status.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}

ServiceSwitchPower.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceSwitchPower.prototype.Variables = function(){
	return this.iVariables;
}

ServiceSwitchPower.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceSwitchPower.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceSwitchPower.prototype.Udn = function () {
    return this.iUdn;
}

ServiceSwitchPower.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceSwitchPower.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceSwitchPower.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceSwitchPower.prototype.SetTarget = function(newTargetValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("newTargetValue", newTargetValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceSwitchPower.prototype.GetTarget = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["RetTargetValue"] = SoapRequest.ReadBoolParameter(result["RetTargetValue"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceSwitchPower.prototype.GetStatus = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStatus", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ResultStatus"] = SoapRequest.ReadBoolParameter(result["ResultStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



