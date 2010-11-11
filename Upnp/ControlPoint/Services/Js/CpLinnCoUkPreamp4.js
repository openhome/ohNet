 

/**
 * Proxy for linn.co.uk:Preamp:4
 */

var ServicePreamp = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Preamp-4/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Preamp";
	this.iVersion = "4";
	this.iServiceName = "linn.co.uk-Preamp-4";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Volume"] = new ServiceVariable("Volume");
		this.iVariables["Mute"] = new ServiceVariable("Mute");
		this.iVariables["Balance"] = new ServiceVariable("Balance");
		this.iVariables["VolumeLimit"] = new ServiceVariable("VolumeLimit");
		this.iVariables["StartupVolume"] = new ServiceVariable("StartupVolume");
		this.iVariables["StartupVolumeEnabled"] = new ServiceVariable("StartupVolumeEnabled");
		this.iVariables["typeString"] = new ServiceVariable("typeString");
		this.iVariables["typeBool"] = new ServiceVariable("typeBool");
		this.iVariables["typeI4"] = new ServiceVariable("typeI4");
		this.iVariables["typeUi4"] = new ServiceVariable("typeUi4");
}


ServicePreamp.prototype.Volume_Changed = function (aStateChangedFunction) {
    this.Variables().Volume.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePreamp.prototype.Mute_Changed = function (aStateChangedFunction) {
    this.Variables().Mute.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePreamp.prototype.Balance_Changed = function (aStateChangedFunction) {
    this.Variables().Balance.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePreamp.prototype.VolumeLimit_Changed = function (aStateChangedFunction) {
    this.Variables().VolumeLimit.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePreamp.prototype.StartupVolume_Changed = function (aStateChangedFunction) {
    this.Variables().StartupVolume.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePreamp.prototype.StartupVolumeEnabled_Changed = function (aStateChangedFunction) {
    this.Variables().StartupVolumeEnabled.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePreamp.prototype.typeString_Changed = function (aStateChangedFunction) {
    this.Variables().typeString.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServicePreamp.prototype.typeBool_Changed = function (aStateChangedFunction) {
    this.Variables().typeBool.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePreamp.prototype.typeI4_Changed = function (aStateChangedFunction) {
    this.Variables().typeI4.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePreamp.prototype.typeUi4_Changed = function (aStateChangedFunction) {
    this.Variables().typeUi4.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServicePreamp.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServicePreamp.prototype.Variables = function(){
	return this.iVariables;
}

ServicePreamp.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServicePreamp.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServicePreamp.prototype.Udn = function () {
    return this.iUdn;
}

ServicePreamp.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServicePreamp.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServicePreamp.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServicePreamp.prototype.VolumeInc = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("VolumeInc", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.VolumeDec = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("VolumeDec", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetVolume = function(aVolume, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVolume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aVolume", aVolume);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.Volume = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Volume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aVolume"] = SoapRequest.ReadIntParameter(result["aVolume"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetMute = function(aMute, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetMute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aMute", aMute);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.Mute = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Mute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMute"] = SoapRequest.ReadBoolParameter(result["aMute"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetBalance = function(aBalance, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBalance", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aBalance", aBalance);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.Balance = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Balance", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aBalance"] = SoapRequest.ReadIntParameter(result["aBalance"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetVolumeLimit = function(aVolumeLimit, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVolumeLimit", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aVolumeLimit", aVolumeLimit);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.VolumeLimit = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("VolumeLimit", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aVolumeLimit"] = SoapRequest.ReadIntParameter(result["aVolumeLimit"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetStartupVolume = function(aStartupVolume, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStartupVolume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aStartupVolume", aStartupVolume);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.StartupVolume = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartupVolume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStartupVolume"] = SoapRequest.ReadIntParameter(result["aStartupVolume"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.SetStartupVolumeEnabled = function(aStartupVolumeEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStartupVolumeEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aStartupVolumeEnabled", aStartupVolumeEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePreamp.prototype.StartupVolumeEnabled = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartupVolumeEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStartupVolumeEnabled"] = SoapRequest.ReadBoolParameter(result["aStartupVolumeEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



