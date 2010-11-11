 

/**
 * Proxy for linn.co.uk:Ptest:1
 */

var ServicePtest = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Ptest-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Ptest";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Ptest-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Bool"] = new ServiceVariable("Bool");
		this.iVariables["ComPort"] = new ServiceVariable("ComPort");
}


ServicePtest.prototype.Bool_Changed = function (aStateChangedFunction) {
    this.Variables().Bool.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePtest.prototype.ComPort_Changed = function (aStateChangedFunction) {
    this.Variables().ComPort.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServicePtest.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServicePtest.prototype.Variables = function(){
	return this.iVariables;
}

ServicePtest.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServicePtest.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServicePtest.prototype.Udn = function () {
    return this.iUdn;
}

ServicePtest.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServicePtest.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServicePtest.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServicePtest.prototype.TestComPort = function(aPort, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TestComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPort", aPort);
    request.Send(function(result){
		result["aResult"] = SoapRequest.ReadBoolParameter(result["aResult"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePtest.prototype.LedsOn = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LedsOn", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePtest.prototype.LedsOff = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LedsOff", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



