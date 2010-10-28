 

/**
 * Proxy for linn.co.uk:ProxyManager:1
 */

var ServiceProxyManager = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/ProxyManager/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ProxyManager";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["KontrolProductConnected"] = new ServiceVariable("KontrolProductConnected");
		this.iVariables["KontrolProductComPort"] = new ServiceVariable("KontrolProductComPort");
		this.iVariables["DiscPlayerConnected"] = new ServiceVariable("DiscPlayerConnected");
		this.iVariables["DiscPlayerComPort"] = new ServiceVariable("DiscPlayerComPort");
		this.iVariables["Bool"] = new ServiceVariable("Bool");
		this.iVariables["ComPort"] = new ServiceVariable("ComPort");
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

ServiceProxyManager.prototype.ServiceName = function(){
	return this.iType;
}

ServiceProxyManager.prototype.Variables = function(){
	return this.iVariables;
}

ServiceProxyManager.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceProxyManager.prototype.KontrolProductConnected = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("KontrolProductConnected", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aConnected"] = request.ReadStringParameter(result["aConnected"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.SetKontrolProductConnected = function(aConnected, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetKontrolProductConnected", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aConnected", aConnected);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.KontrolProductComPort = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("KontrolProductComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPort"] = request.ReadIntParameter(result["aPort"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.SetKontrolProductComPort = function(aConnected, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetKontrolProductComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aConnected", aConnected);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.DiscPlayerConnected = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DiscPlayerConnected", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aConnected"] = request.ReadStringParameter(result["aConnected"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.SetDiscPlayerConnected = function(aConnected, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDiscPlayerConnected", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aConnected", aConnected);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.DiscPlayerComPort = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DiscPlayerComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPort"] = request.ReadIntParameter(result["aPort"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.SetDiscPlayerComPort = function(aConnected, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDiscPlayerComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aConnected", aConnected);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.TestKontrolProductConnection = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TestKontrolProductConnection", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aResult"] = request.ReadBoolParameter(result["aResult"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProxyManager.prototype.TestDiscPlayerConnection = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TestDiscPlayerConnection", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aResult"] = request.ReadBoolParameter(result["aResult"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


