 

/**
 * Proxy for linn.co.uk:Diagnostics:1
 */

var ServiceDiagnostics = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Diagnostics/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Diagnostics";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["aStateVariable"] = new ServiceVariable("aStateVariable");
		this.iVariables["Data"] = new ServiceVariable("Data");
		this.iVariables["String"] = new ServiceVariable("String");
		this.iVariables["Bool"] = new ServiceVariable("Bool");
		this.iVariables["TUint"] = new ServiceVariable("TUint");
}


ServiceDiagnostics.prototype.ServiceName = function(){
	return this.iType;
}

ServiceDiagnostics.prototype.Variables = function(){
	return this.iVariables;
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


ServiceDiagnostics.prototype.Echo = function(aIn, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Echo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aIn", aIn);
    request.Send(function(result){
		result["aOut"] = request.ReadStringParameter(result["aOut"]);	
	
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
		result["aElfFile"] = request.ReadStringParameter(result["aElfFile"]);	
	
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
		result["aElfFileFingerprint"] = request.ReadStringParameter(result["aElfFileFingerprint"]);	
	
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
		result["aCrashDataStatus"] = request.ReadStringParameter(result["aCrashDataStatus"]);	
	
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
		result["aCrashData"] = request.ReadBinaryParameter(result["aCrashData"]);	
	
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
		result["aSysLog"] = request.ReadBinaryParameter(result["aSysLog"]);	
	
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
		result["aDiagnosticInfo"] = request.ReadStringParameter(result["aDiagnosticInfo"]);	
	
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
		result["aStateVariable"] = request.ReadIntParameter(result["aStateVariable"]);	
	
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
		result["aPeriod"] = request.ReadIntParameter(result["aPeriod"]);	
	
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
    


