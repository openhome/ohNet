 

/**
 * Proxy for zapp.org:TestDimmableLight:1
 */

var ServiceTestDimmableLight = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/zapp.org-TestDimmableLight-1/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestDimmableLight";
	this.iVersion = "1";
	this.iServiceName = "zapp.org-TestDimmableLight-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["A_ARG_Level"] = new ServiceVariable("A_ARG_Level");
}


ServiceTestDimmableLight.prototype.A_ARG_Level_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Level.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceTestDimmableLight.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceTestDimmableLight.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestDimmableLight.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceTestDimmableLight.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceTestDimmableLight.prototype.Udn = function () {
    return this.iUdn;
}

ServiceTestDimmableLight.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceTestDimmableLight.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceTestDimmableLight.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceTestDimmableLight.prototype.GetLevel = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Level"] = SoapRequest.ReadIntParameter(result["Level"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestDimmableLight.prototype.SetLevel = function(Level, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Level", Level);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



