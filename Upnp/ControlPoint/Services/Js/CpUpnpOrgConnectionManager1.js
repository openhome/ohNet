 

/**
 * Proxy for upnp.org:ConnectionManager:1
 */

var ServiceConnectionManager = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/ConnectionManager/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ConnectionManager";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["SourceProtocolInfo"] = new ServiceVariable("SourceProtocolInfo");
		this.iVariables["SinkProtocolInfo"] = new ServiceVariable("SinkProtocolInfo");
		this.iVariables["CurrentConnectionIDs"] = new ServiceVariable("CurrentConnectionIDs");
		this.iVariables["ConnectionStatus"] = new ServiceVariable("ConnectionStatus");
		this.iVariables["ConnectionManager"] = new ServiceVariable("ConnectionManager");
		this.iVariables["Direction"] = new ServiceVariable("Direction");
		this.iVariables["ProtocolInfo"] = new ServiceVariable("ProtocolInfo");
		this.iVariables["ConnectionID"] = new ServiceVariable("ConnectionID");
		this.iVariables["AVTransportID"] = new ServiceVariable("AVTransportID");
		this.iVariables["RcsID"] = new ServiceVariable("RcsID");
}

ServiceConnectionManager.kConnectionStatusOk = "OK";
ServiceConnectionManager.kConnectionStatusContentFormatMismatch = "ContentFormatMismatch";
ServiceConnectionManager.kConnectionStatusInsufficientBandwidth = "InsufficientBandwidth";
ServiceConnectionManager.kConnectionStatusUnreliableChannel = "UnreliableChannel";
ServiceConnectionManager.kConnectionStatusUnknown = "Unknown";
ServiceConnectionManager.kDirectionInput = "Input";
ServiceConnectionManager.kDirectionOutput = "Output";

ServiceConnectionManager.prototype.ServiceName = function(){
	return this.iType;
}

ServiceConnectionManager.prototype.Variables = function(){
	return this.iVariables;
}

ServiceConnectionManager.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceConnectionManager.prototype.GetProtocolInfo = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetProtocolInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Source"] = request.ReadStringParameter(result["Source"]);	
		result["Sink"] = request.ReadStringParameter(result["Sink"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConnectionManager.prototype.PrepareForConnection = function(RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PrepareForConnection", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RemoteProtocolInfo", RemoteProtocolInfo);
    request.WriteStringParameter("PeerConnectionManager", PeerConnectionManager);
    request.WriteIntParameter("PeerConnectionID", PeerConnectionID);
    request.WriteStringParameter("Direction", Direction);
    request.Send(function(result){
		result["ConnectionID"] = request.ReadIntParameter(result["ConnectionID"]);	
		result["AVTransportID"] = request.ReadIntParameter(result["AVTransportID"]);	
		result["RcsID"] = request.ReadIntParameter(result["RcsID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConnectionManager.prototype.ConnectionComplete = function(ConnectionID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ConnectionComplete", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("ConnectionID", ConnectionID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConnectionManager.prototype.GetCurrentConnectionIDs = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetCurrentConnectionIDs", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ConnectionIDs"] = request.ReadStringParameter(result["ConnectionIDs"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConnectionManager.prototype.GetCurrentConnectionInfo = function(ConnectionID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetCurrentConnectionInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("ConnectionID", ConnectionID);
    request.Send(function(result){
		result["RcsID"] = request.ReadIntParameter(result["RcsID"]);	
		result["AVTransportID"] = request.ReadIntParameter(result["AVTransportID"]);	
		result["ProtocolInfo"] = request.ReadStringParameter(result["ProtocolInfo"]);	
		result["PeerConnectionManager"] = request.ReadStringParameter(result["PeerConnectionManager"]);	
		result["PeerConnectionID"] = request.ReadIntParameter(result["PeerConnectionID"]);	
		result["Direction"] = request.ReadStringParameter(result["Direction"]);	
		result["Status"] = request.ReadStringParameter(result["Status"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


