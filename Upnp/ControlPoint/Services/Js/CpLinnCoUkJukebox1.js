 

/**
 * Proxy for linn.co.uk:Jukebox:1
 */

var ServiceJukebox = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Jukebox-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Jukebox";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Jukebox-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["MetaData"] = new ServiceVariable("MetaData");
		this.iVariables["CurrentPreset"] = new ServiceVariable("CurrentPreset");
		this.iVariables["PresetPrefix"] = new ServiceVariable("PresetPrefix");
		this.iVariables["AlbumArtFileName"] = new ServiceVariable("AlbumArtFileName");
}


ServiceJukebox.prototype.MetaData_Changed = function (aStateChangedFunction) {
    this.Variables().MetaData.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceJukebox.prototype.CurrentPreset_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentPreset.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceJukebox.prototype.PresetPrefix_Changed = function (aStateChangedFunction) {
    this.Variables().PresetPrefix.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceJukebox.prototype.AlbumArtFileName_Changed = function (aStateChangedFunction) {
    this.Variables().AlbumArtFileName.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceJukebox.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceJukebox.prototype.Variables = function(){
	return this.iVariables;
}

ServiceJukebox.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceJukebox.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceJukebox.prototype.Udn = function () {
    return this.iUdn;
}

ServiceJukebox.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceJukebox.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceJukebox.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceJukebox.prototype.SetPresetPrefix = function(aUri, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetPrefix", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aUri", aUri);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.PresetPrefix = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetPrefix", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUri"] = SoapRequest.ReadStringParameter(result["aUri"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.SetAlbumArtFileName = function(aName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetAlbumArtFileName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aName", aName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.AlbumArtFileName = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("AlbumArtFileName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aName"] = SoapRequest.ReadStringParameter(result["aName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.SetCurrentPreset = function(aPreset, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetCurrentPreset", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPreset", aPreset);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.CurrentPreset = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CurrentPreset", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPreset"] = SoapRequest.ReadIntParameter(result["aPreset"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.PresetMetaData = function(aPreset, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetMetaData", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPreset", aPreset);
    request.Send(function(result){
		result["aMetaData"] = SoapRequest.ReadStringParameter(result["aMetaData"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceJukebox.prototype.LoadManifest = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LoadManifest", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTotalPresets"] = SoapRequest.ReadIntParameter(result["aTotalPresets"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



