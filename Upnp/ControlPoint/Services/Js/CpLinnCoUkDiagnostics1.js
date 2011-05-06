 

/**
* Service Proxy for CpProxyLinnCoUkDiagnostics1
* @module Zapp
* @class Diagnostics
*/
	
var CpProxyLinnCoUkDiagnostics1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Diagnostics-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Diagnostics";
	this.version = "1";
	this.serviceName = "linn.co.uk-Diagnostics-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["aStateVariable"] = new Zapp.ServiceProperty("aStateVariable","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkDiagnostics1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkDiagnostics1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "aStateVariable" property change events
* @method aStateVariable_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDiagnostics1.prototype.aStateVariable_Changed = function (stateChangedFunction) {
    this.serviceProperties.aStateVariable.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Echo
* @method Echo
* @param {String} aIn An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.Echo = function(aIn, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Echo", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aIn", aIn);
    request.send(function(result){
		result["aOut"] = Zapp.SoapRequest.readStringParameter(result["aOut"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ElfFile
* @method ElfFile
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.ElfFile = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ElfFile", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aElfFile"] = Zapp.SoapRequest.readStringParameter(result["aElfFile"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ElfFingerprint
* @method ElfFingerprint
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.ElfFingerprint = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ElfFingerprint", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aElfFileFingerprint"] = Zapp.SoapRequest.readStringParameter(result["aElfFileFingerprint"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataStatus
* @method CrashDataStatus
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.CrashDataStatus = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataStatus", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aCrashDataStatus"] = Zapp.SoapRequest.readStringParameter(result["aCrashDataStatus"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataFetch
* @method CrashDataFetch
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.CrashDataFetch = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataFetch", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aCrashData"] = Zapp.SoapRequest.readBinaryParameter(result["aCrashData"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataClear
* @method CrashDataClear
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.CrashDataClear = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataClear", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SysLog
* @method SysLog
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.SysLog = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SysLog", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSysLog"] = Zapp.SoapRequest.readBinaryParameter(result["aSysLog"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Diagnostic
* @method Diagnostic
* @param {String} aDiagnosticType An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.Diagnostic = function(aDiagnosticType, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Diagnostic", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aDiagnosticType", aDiagnosticType);
    request.send(function(result){
		result["aDiagnosticInfo"] = Zapp.SoapRequest.readStringParameter(result["aDiagnosticInfo"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StateVariable
* @method StateVariable
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.StateVariable = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StateVariable", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aStateVariable"] = Zapp.SoapRequest.readIntParameter(result["aStateVariable"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStateVariable
* @method SetStateVariable
* @param {Int} aStateVariable An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.SetStateVariable = function(aStateVariable, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStateVariable", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aStateVariable", aStateVariable);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StateVariablePeriod
* @method StateVariablePeriod
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.StateVariablePeriod = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StateVariablePeriod", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aPeriod"] = Zapp.SoapRequest.readIntParameter(result["aPeriod"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStateVariablePeriod
* @method SetStateVariablePeriod
* @param {Int} aPeriod An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.SetStateVariablePeriod = function(aPeriod, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStateVariablePeriod", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aPeriod", aPeriod);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Reboot
* @method Reboot
* @param {Int} aDelay An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDiagnostics1.prototype.Reboot = function(aDelay, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Reboot", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aDelay", aDelay);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



