 

/**
 * Proxy for linn.co.uk:Configuration:1
 */

var ServiceConfiguration = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Configuration-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Configuration";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Configuration-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["ConfigurationXml"] = new ServiceVariable("ConfigurationXml");
		this.iVariables["ParameterXml"] = new ServiceVariable("ParameterXml");
		this.iVariables["Target"] = new ServiceVariable("Target");
		this.iVariables["Name"] = new ServiceVariable("Name");
		this.iVariables["Value"] = new ServiceVariable("Value");
}


ServiceConfiguration.prototype.ConfigurationXml_Changed = function (aStateChangedFunction) {
    this.Variables().ConfigurationXml.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConfiguration.prototype.ParameterXml_Changed = function (aStateChangedFunction) {
    this.Variables().ParameterXml.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConfiguration.prototype.Target_Changed = function (aStateChangedFunction) {
    this.Variables().Target.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConfiguration.prototype.Name_Changed = function (aStateChangedFunction) {
    this.Variables().Name.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceConfiguration.prototype.Value_Changed = function (aStateChangedFunction) {
    this.Variables().Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceConfiguration.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceConfiguration.prototype.Variables = function(){
	return this.iVariables;
}

ServiceConfiguration.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceConfiguration.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceConfiguration.prototype.Udn = function () {
    return this.iUdn;
}

ServiceConfiguration.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceConfiguration.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceConfiguration.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceConfiguration.prototype.ConfigurationXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ConfigurationXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aConfigurationXml"] = SoapRequest.ReadStringParameter(result["aConfigurationXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceConfiguration.prototype.ParameterXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ParameterXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aParameterXml"] = SoapRequest.ReadStringParameter(result["aParameterXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceConfiguration.prototype.SetParameter = function(aTarget, aName, aValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetParameter", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aTarget", aTarget);
    request.WriteStringParameter("aName", aName);
    request.WriteStringParameter("aValue", aValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



