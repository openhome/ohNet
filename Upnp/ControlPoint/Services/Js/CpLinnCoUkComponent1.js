 

/**
 * Proxy for linn.co.uk:Component:1
 */

var ServiceComponent = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Component-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Component";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Component-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["AmplifierEnabled"] = new ServiceVariable("AmplifierEnabled");
		this.iVariables["AmplifierAttenuation"] = new ServiceVariable("AmplifierAttenuation");
		this.iVariables["VolumeControlEnabled"] = new ServiceVariable("VolumeControlEnabled");
		this.iVariables["DigitalAudioOutputRaw"] = new ServiceVariable("DigitalAudioOutputRaw");
		this.iVariables["Bool"] = new ServiceVariable("Bool");
}

ServiceComponent.kAmplifierAttenuation12Db = "-12dB";
ServiceComponent.kAmplifierAttenuation9Db = "-9dB";
ServiceComponent.kAmplifierAttenuation6Db = "-6dB";
ServiceComponent.kAmplifierAttenuation0Db = "0dB";

ServiceComponent.prototype.AmplifierEnabled_Changed = function (aStateChangedFunction) {
    this.Variables().AmplifierEnabled.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceComponent.prototype.AmplifierAttenuation_Changed = function (aStateChangedFunction) {
    this.Variables().AmplifierAttenuation.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceComponent.prototype.VolumeControlEnabled_Changed = function (aStateChangedFunction) {
    this.Variables().VolumeControlEnabled.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceComponent.prototype.DigitalAudioOutputRaw_Changed = function (aStateChangedFunction) {
    this.Variables().DigitalAudioOutputRaw.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceComponent.prototype.Bool_Changed = function (aStateChangedFunction) {
    this.Variables().Bool.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}

ServiceComponent.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceComponent.prototype.Variables = function(){
	return this.iVariables;
}

ServiceComponent.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceComponent.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceComponent.prototype.Udn = function () {
    return this.iUdn;
}

ServiceComponent.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceComponent.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceComponent.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceComponent.prototype.AmplifierEnabled = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("AmplifierEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aEnabled"] = SoapRequest.ReadBoolParameter(result["aEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.SetAmplifierEnabled = function(aEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetAmplifierEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aEnabled", aEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.AmplifierAttenuation = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("AmplifierAttenuation", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aAttenuation"] = SoapRequest.ReadStringParameter(result["aAttenuation"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.SetAmplifierAttenuation = function(aAttenuation, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetAmplifierAttenuation", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aAttenuation", aAttenuation);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.SetVolumeControlEnabled = function(aEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVolumeControlEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aEnabled", aEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.VolumeControlEnabled = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("VolumeControlEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aEnabled"] = SoapRequest.ReadBoolParameter(result["aEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.SetDigitalAudioOutputRaw = function(aRaw, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDigitalAudioOutputRaw", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aRaw", aRaw);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.DigitalAudioOutputRaw = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DigitalAudioOutputRaw", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aRaw"] = SoapRequest.ReadBoolParameter(result["aRaw"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.AmplifierOverTemperature = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("AmplifierOverTemperature", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aOverTemperature"] = SoapRequest.ReadBoolParameter(result["aOverTemperature"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.EthernetLinkConnected = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("EthernetLinkConnected", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aLinkConnected"] = SoapRequest.ReadBoolParameter(result["aLinkConnected"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceComponent.prototype.Locate = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Locate", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



