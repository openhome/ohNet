 

/**
 * Proxy for linn.co.uk:Diagnostics:1
 */

var ServiceDiagnostics = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Diagnostics-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Diagnostics";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Diagnostics-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["aStateVariable"] = new ServiceVariable("aStateVariable");
		this.iVariables["Data"] = new ServiceVariable("Data");
		this.iVariables["String"] = new ServiceVariable("String");
		this.iVariables["Bool"] = new ServiceVariable("Bool");
		this.iVariables["TUint"] = new ServiceVariable("TUint");
}


ServiceDiagnostics.prototype.aStateVariable_Changed = function (aStateChangedFunction) {
    this.Variables().aStateVariable.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDiagnostics.prototype.Data_Changed = function (aStateChangedFunction) {
    this.Variables().Data.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}
ServiceDiagnostics.prototype.String_Changed = function (aStateChangedFunction) {
    this.Variables().String.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDiagnostics.prototype.Bool_Changed = function (aStateChangedFunction) {
    this.Variables().Bool.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceDiagnostics.prototype.TUint_Changed = function (aStateChangedFunction) {
    this.Variables().TUint.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceDiagnostics.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceDiagnostics.prototype.Variables = function(){
	return this.iVariables;
}

ServiceDiagnostics.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceDiagnostics.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceDiagnostics.prototype.Udn = function () {
    return this.iUdn;
}

ServiceDiagnostics.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceDiagnostics.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceDiagnostics.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceDiagnostics.prototype.Echo = function(aIn, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Echo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aIn", aIn);
    request.Send(function(result){
		result["aOut"] = SoapRequest.ReadStringParameter(result["aOut"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.ElfFile = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ElfFile", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aElfFile"] = SoapRequest.ReadStringParameter(result["aElfFile"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.ElfFingerprint = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ElfFingerprint", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aElfFileFingerprint"] = SoapRequest.ReadStringParameter(result["aElfFileFingerprint"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.CrashDataStatus = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CrashDataStatus", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aCrashDataStatus"] = SoapRequest.ReadStringParameter(result["aCrashDataStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.CrashDataFetch = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CrashDataFetch", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aCrashData"] = SoapRequest.ReadBinaryParameter(result["aCrashData"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.CrashDataClear = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CrashDataClear", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.SysLog = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SysLog", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSysLog"] = SoapRequest.ReadBinaryParameter(result["aSysLog"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.Diagnostic = function(aDiagnosticType, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Diagnostic", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aDiagnosticType", aDiagnosticType);
    request.Send(function(result){
		result["aDiagnosticInfo"] = SoapRequest.ReadStringParameter(result["aDiagnosticInfo"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.StateVariable = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StateVariable", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStateVariable"] = SoapRequest.ReadIntParameter(result["aStateVariable"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.SetStateVariable = function(aStateVariable, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStateVariable", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aStateVariable", aStateVariable);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.StateVariablePeriod = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StateVariablePeriod", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPeriod"] = SoapRequest.ReadIntParameter(result["aPeriod"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.SetStateVariablePeriod = function(aPeriod, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStateVariablePeriod", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPeriod", aPeriod);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDiagnostics.prototype.Reboot = function(aDelay, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Reboot", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aDelay", aDelay);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



