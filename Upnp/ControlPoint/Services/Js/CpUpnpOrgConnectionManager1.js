 

/**
 * Proxy for upnp.org:ConnectionManager:1
 */

var ServiceConnectionManager = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-ConnectionManager-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ConnectionManager";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-ConnectionManager-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
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

ServiceConnectionManager.prototype.SourceProtocolInfo_Changed = function (aStateChangedFunction) {
    this.Variables().SourceProtocolInfo.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.SinkProtocolInfo_Changed = function (aStateChangedFunction) {
    this.Variables().SinkProtocolInfo.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.CurrentConnectionIDs_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentConnectionIDs.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.ConnectionStatus_Changed = function (aStateChangedFunction) {
    this.Variables().ConnectionStatus.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.ConnectionManager_Changed = function (aStateChangedFunction) {
    this.Variables().ConnectionManager.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.Direction_Changed = function (aStateChangedFunction) {
    this.Variables().Direction.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.ProtocolInfo_Changed = function (aStateChangedFunction) {
    this.Variables().ProtocolInfo.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConnectionManager.prototype.ConnectionID_Changed = function (aStateChangedFunction) {
    this.Variables().ConnectionID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceConnectionManager.prototype.AVTransportID_Changed = function (aStateChangedFunction) {
    this.Variables().AVTransportID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceConnectionManager.prototype.RcsID_Changed = function (aStateChangedFunction) {
    this.Variables().RcsID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceConnectionManager.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceConnectionManager.prototype.Variables = function(){
	return this.iVariables;
}

ServiceConnectionManager.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceConnectionManager.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceConnectionManager.prototype.Udn = function () {
    return this.iUdn;
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

ServiceConnectionManager.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceConnectionManager.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceConnectionManager.prototype.GetProtocolInfo = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetProtocolInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Source"] = SoapRequest.ReadStringParameter(result["Source"]);	
		result["Sink"] = SoapRequest.ReadStringParameter(result["Sink"]);	
	
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
		result["ConnectionID"] = SoapRequest.ReadIntParameter(result["ConnectionID"]);	
		result["AVTransportID"] = SoapRequest.ReadIntParameter(result["AVTransportID"]);	
		result["RcsID"] = SoapRequest.ReadIntParameter(result["RcsID"]);	
	
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
		result["ConnectionIDs"] = SoapRequest.ReadStringParameter(result["ConnectionIDs"]);	
	
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
		result["RcsID"] = SoapRequest.ReadIntParameter(result["RcsID"]);	
		result["AVTransportID"] = SoapRequest.ReadIntParameter(result["AVTransportID"]);	
		result["ProtocolInfo"] = SoapRequest.ReadStringParameter(result["ProtocolInfo"]);	
		result["PeerConnectionManager"] = SoapRequest.ReadStringParameter(result["PeerConnectionManager"]);	
		result["PeerConnectionID"] = SoapRequest.ReadIntParameter(result["PeerConnectionID"]);	
		result["Direction"] = SoapRequest.ReadStringParameter(result["Direction"]);	
		result["Status"] = SoapRequest.ReadStringParameter(result["Status"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



