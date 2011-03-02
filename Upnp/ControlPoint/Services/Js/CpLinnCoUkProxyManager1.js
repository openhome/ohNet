 

/**
* Service Proxy for CpProxyLinnCoUkProxyManager1
* @module Zapp
* @class ProxyManager
*/
	
var CpProxyLinnCoUkProxyManager1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-ProxyManager-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "ProxyManager";
	this.version = "1";
	this.serviceName = "linn.co.uk-ProxyManager-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["KontrolProductConnected"] = new Zapp.ServiceProperty("KontrolProductConnected");
	this.serviceProperties["KontrolProductComPort"] = new Zapp.ServiceProperty("KontrolProductComPort");
	this.serviceProperties["DiscPlayerConnected"] = new Zapp.ServiceProperty("DiscPlayerConnected");
	this.serviceProperties["DiscPlayerComPort"] = new Zapp.ServiceProperty("DiscPlayerComPort");
}

ServiceProxyManager.kKontrolProductConnectedNone = "None";
ServiceProxyManager.kKontrolProductConnectedKlimaxKontrol = "Klimax Kontrol";
ServiceProxyManager.kKontrolProductConnectedAkurateKontrol = "Akurate Kontrol";
ServiceProxyManager.kKontrolProductConnectedKisto = "Kisto";
ServiceProxyManager.kKontrolProductConnectedKinos = "Kinos";
ServiceProxyManager.kKontrolProductConnectedMajikKontrol = "Majik Kontrol";
ServiceProxyManager.kKontrolProductConnectedMajikI = "Majik-I";
ServiceProxyManager.kKontrolProductConnectedUnidiskSc = "Unidisk SC";
ServiceProxyManager.kKontrolProductConnectedClassikMovie = "Classik Movie";
ServiceProxyManager.kKontrolProductConnectedClassikMusic = "Classik Music";
ServiceProxyManager.kKontrolProductConnectedRoomamp2 = "Roomamp 2";
ServiceProxyManager.kDiscPlayerConnectedNone = "None";
ServiceProxyManager.kDiscPlayerConnectedCd12 = "CD12";
ServiceProxyManager.kDiscPlayerConnectedAkurateCd = "Akurate CD";
ServiceProxyManager.kDiscPlayerConnectedUnidisk11 = "Unidisk 1.1";
ServiceProxyManager.kDiscPlayerConnectedUnidisk21 = "Unidisk 2.1";
ServiceProxyManager.kDiscPlayerConnectedMajikCd = "Majik CD";
ServiceProxyManager.kDiscPlayerConnectedUnidiskSc = "Unidisk SC";
ServiceProxyManager.kDiscPlayerConnectedClassikMovie = "Classik Movie";
ServiceProxyManager.kDiscPlayerConnectedClassikMusic = "Classik Music";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkProxyManager1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkProxyManager1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "KontrolProductConnected" property change events
* @method KontrolProductConnected_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProxyManager1.prototype.KontrolProductConnected_Changed = function (stateChangedFunction) {
    this.serviceProperties.KontrolProductConnected.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "KontrolProductComPort" property change events
* @method KontrolProductComPort_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProxyManager1.prototype.KontrolProductComPort_Changed = function (stateChangedFunction) {
    this.serviceProperties.KontrolProductComPort.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "DiscPlayerConnected" property change events
* @method DiscPlayerConnected_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProxyManager1.prototype.DiscPlayerConnected_Changed = function (stateChangedFunction) {
    this.serviceProperties.DiscPlayerConnected.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "DiscPlayerComPort" property change events
* @method DiscPlayerComPort_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProxyManager1.prototype.DiscPlayerComPort_Changed = function (stateChangedFunction) {
    this.serviceProperties.DiscPlayerComPort.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to KontrolProductConnected
* @method KontrolProductConnected
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.KontrolProductConnected = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("KontrolProductConnected", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aConnected"] = Zapp.SoapRequest.readStringParameter(result["aConnected"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetKontrolProductConnected
* @method SetKontrolProductConnected
* @param {String} aConnected An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.SetKontrolProductConnected = function(aConnected, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetKontrolProductConnected", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aConnected", aConnected);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to KontrolProductComPort
* @method KontrolProductComPort
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.KontrolProductComPort = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("KontrolProductComPort", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aPort"] = Zapp.SoapRequest.readIntParameter(result["aPort"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetKontrolProductComPort
* @method SetKontrolProductComPort
* @param {Int} aConnected An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.SetKontrolProductComPort = function(aConnected, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetKontrolProductComPort", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aConnected", aConnected);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DiscPlayerConnected
* @method DiscPlayerConnected
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.DiscPlayerConnected = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DiscPlayerConnected", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aConnected"] = Zapp.SoapRequest.readStringParameter(result["aConnected"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetDiscPlayerConnected
* @method SetDiscPlayerConnected
* @param {String} aConnected An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.SetDiscPlayerConnected = function(aConnected, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetDiscPlayerConnected", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aConnected", aConnected);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DiscPlayerComPort
* @method DiscPlayerComPort
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.DiscPlayerComPort = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DiscPlayerComPort", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aPort"] = Zapp.SoapRequest.readIntParameter(result["aPort"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetDiscPlayerComPort
* @method SetDiscPlayerComPort
* @param {Int} aConnected An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.SetDiscPlayerComPort = function(aConnected, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetDiscPlayerComPort", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aConnected", aConnected);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to TestKontrolProductConnection
* @method TestKontrolProductConnection
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.TestKontrolProductConnection = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TestKontrolProductConnection", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aResult"] = Zapp.SoapRequest.readBoolParameter(result["aResult"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to TestDiscPlayerConnection
* @method TestDiscPlayerConnection
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProxyManager1.prototype.TestDiscPlayerConnection = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TestDiscPlayerConnection", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aResult"] = Zapp.SoapRequest.readBoolParameter(result["aResult"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



