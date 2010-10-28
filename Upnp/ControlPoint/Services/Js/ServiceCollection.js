var ServiceCollection = function (aPollTimeSeconds){
	this.iServices = {};
	this.iPollTimeSeconds = aPollTimeSeconds?aPollTimeSeconds:ServiceCollection.kDefaultPollTimeSeconds;
}

ServiceCollection.kDefaultPollTimeSeconds = 5;

ServiceCollection.prototype.Start = function(){
	var thisObj = this;
	this.iCallbackTimer = new PeriodicalExecuter(function() { thisObj.GetChanges(); } , this.iPollTimeSeconds);
	this.GetChanges();
}

ServiceCollection.prototype.Stop = function(){
	if (this.iCallbackTimer){
		this.iCallbackTimer.Stop();
		this.iCallbackTimer = null;		
	}
}

ServiceCollection.prototype.AddService = function(aService){
	this.iServices[aService.ServiceName()] = aService;
}

ServiceCollection.prototype.RemoveService = function(aService){
	delete this.iServices[aService.ServiceName()];
}

ServiceCollection.prototype.GetService = function(aServiceName){
	return this.iServices[aServiceName];
}

ServiceCollection.prototype.Services = function(){
	return this.iServices;
}

ServiceCollection.prototype.ServiceNames = function(){
	var result = [];
	for (var srv in this.iServices){
		if (this.iServices.hasOwnProperty(srv)){
			result[result.length] = srv;
		}
	}
	return result;
}

ServiceCollection.prototype.GetChanges = function(){
	var serviceNames = this.ServiceNames();
	for(var i=0;i<serviceNames.length;i++){
		this.GetServiceChanges(this.GetService(serviceNames[i]));		
	}
}

ServiceCollection.prototype.GetServiceChanges = function(aService){
	var thisObj = this;
	var varNames = aService.VariableNames();
		
	if (aService.ServiceName() == "Ds"){				
		thisObj.CallStateGetter(aService);
	}else if (aService.ServiceName() == "Info"){	
		thisObj.CallCountersGetter(aService);
	}else{
		var functionName;
		for (var j=0;j<varNames.length;j++){
			functionName = varNames[j];
			var requestProperty = true;			
			if (aService.ServiceName() == "Product"){
				functionName = functionName.replace(/Product/,"");
				switch (functionName){
					case "SourceIndex":
					case "SourceXml":
					case "Standby":
						break;
					// only want to request the above 3 properties from this service
					default: requestProperty = false;
				}
			}
			if (aService.ServiceName() == "Playlist"){				
				switch (functionName){
					case "IdArray":
						/* ignore IdArray - only handle this on IdArrayChanged = true */
						requestProperty = false;
					default: break;
				}
			}
			if (aService.ServiceName() == "Radio"){				
				switch (functionName){
					case "IdArray":
						/* ignore IdArray - only handle this on IdArrayChanged = true */
						requestProperty = false;
					default: break;
				}
			}
			if (requestProperty){
				var variableName = "a" + functionName;
				if (aService.ServiceName() == "Radio" && functionName == "TransportState"){
					variableName = "aState";
				}
				switch (varNames[j]){
					case "IdArrayChanged":	{				
						thisObj.CallIdArrayChangedGetter(aService);
						break;
					}
					default:{
						if (typeof aService[functionName] == "function"){
							thisObj.CallGenericGetter(aService, functionName, aService.Variables()[varNames[j]], variableName);
						}
					}
				}
			}
		}
	}
}

ServiceCollection.prototype.CallIdArrayChangedGetter = function(aService){
	var thisObj = this;
	if (aService.Variables().IdArray.Listeners().length){
		aService.IdArrayChanged(aService.Variables().IdArrayToken.Value(), function(result){
			aService.Variables().IdArrayChanged.SetValue(result.aIdArrayChanged);
			if (result.aIdArrayChanged){
				thisObj.CallIdArrayGetter(aService);
			}
		},function(message){
			debug.log("Error caught in CallIdArrayChangedGetter: " + message);
		});
	}
}

ServiceCollection.prototype.CallIdArrayGetter = function(aService){
	aService.IdArray(function(result){	
		aService.Variables().IdArray.SetValue(decode64(result.aIdArray));
		aService.Variables().IdArrayToken.SetValue(result.aIdArrayToken);		
	},function(message){
		debug.log("Error caught in CallIdArrayGetter: " + message);
	});
} 

ServiceCollection.prototype.CallStateGetter = function(aService){
	if (aService.Variables().TransportState.Listeners().length || 
		aService.Variables().TrackDuration.Listeners().length || 
		aService.Variables().TrackBitRate.Listeners().length || 
		aService.Variables().TrackLossless.Listeners().length || 
		aService.Variables().TrackBitDepth.Listeners().length || 
		aService.Variables().TrackSampleRate.Listeners().length || 
		aService.Variables().TrackCodecName.Listeners().length || 
		aService.Variables().TrackId.Listeners().length){			
		aService.State(function(result){
			aService.Variables().TransportState.SetValue(result.aTransportState);	
			aService.Variables().TrackDuration.SetValue(result.aTrackDuration);	
			aService.Variables().TrackBitRate.SetValue(result.aTrackBitRate);	
			aService.Variables().TrackLossless.SetValue(result.aTrackLossless);	
			aService.Variables().TrackBitDepth.SetValue(result.aTrackBitDepth);	
			aService.Variables().TrackSampleRate.SetValue(result.aTrackSampleRate);	
			aService.Variables().TrackCodecName.SetValue(result.aTrackCodecName);	
			aService.Variables().TrackId.SetValue(result.aTrackId);	
		},function(message){		
			debug.log("Error caught in CallStateGetter: " + message);
		});
	}
}

ServiceCollection.prototype.CallCountersGetter = function(aService){
	var thisObj = this;
	if (this.HasTrackListeners(aService) || this.HasDetailsListeners(aService) || this.HasMetatextListeners(aService)){
		aService.Counters(function(result){
			var previousTrackCount = aService.Variables().TrackCount.Value();
			aService.Variables().TrackCount.SetValue(result.aTrackCount);
			var trackCountChanged = previousTrackCount != aService.Variables().TrackCount.Value();
			if (trackCountChanged){
				thisObj.CallTrackGetter(aService);		
			}

			var previousDetailsCount = aService.Variables().DetailsCount.Value();
			aService.Variables().DetailsCount.SetValue(result.aDetailsCount);
			var detailsCountChanged = previousDetailsCount != aService.Variables().DetailsCount.Value();
			if (trackCountChanged || detailsCountChanged){
				thisObj.CallDetailsGetter(aService);	
			}
			
			var previousMetatextCount = aService.Variables().MetatextCount.Value();		
			aService.Variables().MetatextCount.SetValue(result.aMetatextCount);		
			var metatextCountChanged = previousMetatextCount != aService.Variables().MetatextCount.Value();
			if (trackCountChanged || metatextCountChanged){
				thisObj.CallGenericGetter(aService, "Metatext", aService.Variables().Metatext, "Metatext");	
			}
		},function(message){
			debug.log("Error caught in CallCountersGetter: " + message);
		});
	}
}

ServiceCollection.prototype.HasTrackListeners = function(aService){
	return aService.Variables().TrackCount.Listeners().length || 		
		aService.Variables().Uri.Listeners().length || 
		aService.Variables().Metadata.Listeners().length;
}

ServiceCollection.prototype.CallTrackGetter = function(aService){
	if (this.HasTrackListeners(aService)){
		aService.Track(function(result){
			aService.Variables().Uri.SetValue(result.aUri);	
			aService.Variables().Metadata.SetValue(result.aMetadata);	
		},function(message){		
			debug.log("Error caught in CallTrackGetter: " + message);
		});
	}
}

ServiceCollection.prototype.HasDetailsListeners = function(aService){
	return aService.Variables().DetailsCount.Listeners().length || 
		aService.Variables().Duration.Listeners().length || 
		aService.Variables().BitRate.Listeners().length || 
		aService.Variables().BitDepth.Listeners().length || 
		aService.Variables().SampleRate.Listeners().length || 
		aService.Variables().Lossless.Listeners().length || 
		aService.Variables().CodecName.Listeners().length;
}

ServiceCollection.prototype.CallDetailsGetter = function(aService){
	if (this.HasDetailsListeners(aService)){		
		aService.Details(function(result){
			aService.Variables().Duration.SetValue(result.aDuration);	
			aService.Variables().BitRate.SetValue(result.aBitRate);	
			aService.Variables().BitDepth.SetValue(result.aBitDepth);	
			aService.Variables().SampleRate.SetValue(result.aSampleRate);	
			aService.Variables().Lossless.SetValue(result.aLossless);	
			aService.Variables().CodecName.SetValue(result.aCodecName);	
		},function(message){		
			debug.log("Error caught in CallDetailsGetter: " + message);
		});
	}
}

ServiceCollection.prototype.HasMetatextListeners = function(aService){
	return aService.Variables().MetatextCount.Listeners().length || 
		aService.Variables().Metatext.Listeners().length;
}

ServiceCollection.prototype.CallMetatextGetter = function(aService){
	if (this.HasMetatextListeners(aService)){		
		aService.Metatext(function(result){
			aService.Variables().Metatext.SetValue(result.aMetatext);	
		},function(message){		
			debug.log("Error caught in CallMetatextGetter: " + message);
		});
	}
}

ServiceCollection.prototype.CallGenericGetter = function(aService, aServiceFunctionName, aServiceVariable, aServiceVariableName){
	if (aServiceVariable.Listeners().length){
		aService[aServiceFunctionName].call(aService,function(result){
			debug.log("CallGenericGetter: " + aServiceFunctionName);
			aServiceVariable.SetValue(result[aServiceVariableName]);
		},function(message, transport){
			if (transport && transport.status && transport.status == "404" && aService.ServiceName() == "Preamp"){		
				// preamp service is not always there - prevent repeated messages to non existent service
				aServiceVariable.Listeners().clear();	
			}
			debug.log("Error caught in CallGenericGetter: " + message);
		});
	}
}

var ServiceVariable = function(aName){
	this.iName = aName;
	this.iValue = null;
	this.iListeners = [];
}

ServiceVariable.prototype.Name = function(){
	return this.iName;
}

ServiceVariable.prototype.Value = function(){
	return this.iValue;
}

ServiceVariable.prototype.SetValue = function(aValue){
	if (this.iValue != aValue){
		this.iValue = aValue;
		for (var i=0;i<this.iListeners.length;i++){
			try{
				this.iListeners[i].call(this, aValue);
			}catch(e){
				debug.log("Error caught in SetValue: " + e);
			}			
		}
	}
}

ServiceVariable.prototype.AddListener = function(aListener){
	this.iListeners[this.iListeners.length] = aListener;
}

ServiceVariable.prototype.RemoveListener = function(aListener){	
	var idx = this.iListeners.indexOf(aListener);
	if (idx != -1){
		this.iListeners.remove(idx);
	}
}

ServiceVariable.prototype.Listeners = function(){
	return this.iListeners;
}
