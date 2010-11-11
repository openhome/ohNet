 

/**
 * Proxy for linn.co.uk:Volkano:1
 */

var ServiceVolkano = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Volkano-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Volkano";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Volkano-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["BootMode"] = new ServiceVariable("BootMode");
		this.iVariables["RebootMode"] = new ServiceVariable("RebootMode");
		this.iVariables["String"] = new ServiceVariable("String");
		this.iVariables["TUint"] = new ServiceVariable("TUint");
}

ServiceVolkano.kBootModeMain = "Main";
ServiceVolkano.kBootModeFallback = "Fallback";
ServiceVolkano.kBootModeRam = "Ram";
ServiceVolkano.kRebootModeMain = "Main";
ServiceVolkano.kRebootModeFallback = "Fallback";

ServiceVolkano.prototype.BootMode_Changed = function (aStateChangedFunction) {
    this.Variables().BootMode.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceVolkano.prototype.RebootMode_Changed = function (aStateChangedFunction) {
    this.Variables().RebootMode.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceVolkano.prototype.String_Changed = function (aStateChangedFunction) {
    this.Variables().String.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceVolkano.prototype.TUint_Changed = function (aStateChangedFunction) {
    this.Variables().TUint.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceVolkano.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceVolkano.prototype.Variables = function(){
	return this.iVariables;
}

ServiceVolkano.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceVolkano.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceVolkano.prototype.Udn = function () {
    return this.iUdn;
}

ServiceVolkano.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceVolkano.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceVolkano.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceVolkano.prototype.Reboot = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Reboot", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.BootMode = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BootMode", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMode"] = SoapRequest.ReadStringParameter(result["aMode"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.SetBootMode = function(aMode, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBootMode", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aMode", aMode);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.BspType = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BspType", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aBspType"] = SoapRequest.ReadStringParameter(result["aBspType"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.UglyName = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("UglyName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUglyName"] = SoapRequest.ReadStringParameter(result["aUglyName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.MacAddress = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("MacAddress", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMacAddress"] = SoapRequest.ReadStringParameter(result["aMacAddress"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.ProductId = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ProductId", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aProductNumber"] = SoapRequest.ReadStringParameter(result["aProductNumber"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.BoardId = function(aIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BoardId", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.Send(function(result){
		result["aBoardNumber"] = SoapRequest.ReadStringParameter(result["aBoardNumber"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.BoardType = function(aIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BoardType", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.Send(function(result){
		result["aBoardNumber"] = SoapRequest.ReadStringParameter(result["aBoardNumber"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.MaxBoards = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("MaxBoards", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMaxBoards"] = SoapRequest.ReadIntParameter(result["aMaxBoards"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceVolkano.prototype.SoftwareVersion = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SoftwareVersion", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSoftwareVersion"] = SoapRequest.ReadStringParameter(result["aSoftwareVersion"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



