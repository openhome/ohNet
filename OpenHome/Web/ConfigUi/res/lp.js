WebUi = function() {

    var gLongPoll = null;
    var gStarted = false;

    // Create a wrapper for XMLHttpRequest that will automatically include any
    // URI resource prefix in open() calls.
    var HttpRequest = function()
    {
        this.iRequest = null;
        this.iPrefix = HttpRequest.GetResourcePrefix();
        // XMLHttpRequest construction taken from
        // http://www.w3schools.com/ajax/ajax_xmlhttprequest_create.asp
        if (window.XMLHttpRequest)
        {// code for IE7+, Firefox, Chrome, Opera, Safari
            this.iRequest = new XMLHttpRequest();
        }
        else
        {// code for IE6, IE5
            this.iRequest = new ActiveXObject("Microsoft.XMLHTTP");
        }
    }

    HttpRequest.prototype.ReadyState = function()
    {
        return this.iRequest.readyState;
    }

    HttpRequest.prototype.Status = function()
    {
        return this.iRequest.status;
    }

    HttpRequest.prototype.Open = function(aMethod, aUrl, aAsync)
    {
        this.iRequest.open(aMethod, aUrl, aAsync);
    }

    HttpRequest.prototype.SetRequestHeader = function(aHeader, aValue)
    {
        this.iRequest.setRequestHeader(aHeader, aValue);
    }

    HttpRequest.prototype.Send = function(aString)
    {
        this.iRequest.send(aString);
    }

    HttpRequest.prototype.ResponseUrl = function()
    {
        return this.iRequest.responseURL;
    }

    HttpRequest.prototype.ResponseText = function()
    {
        return this.iRequest.responseText;
    }

    HttpRequest.prototype.SetOnReadyStateChange = function(aCallbackResponse)
    {
        this.iRequest.onreadystatechange = aCallbackResponse;
    }

    HttpRequest.prototype.AddEventListener = function(aEvent, aCallback, aCapture)
    {
        this.iRequest.addEventListener(aEvent, aCallback, aCapture);
    }

    HttpRequest.GetResourcePrefix = function()
    {
        var url = document.URL;
        var urlSplit = url.split("/");
        if (urlSplit.length > 1) {
            return urlSplit[urlSplit.length-2];
        }
        else {
            return "";
        }
    }

    var CreateResponseCallback = function(aLongPoll, aRequest)
    {
        return function() {
            aLongPoll.ProcessResponse(aRequest);
        }
    }

    // When "this.SendCreate" is passed into a setTimeout call, in SendCreate()
    // "this" ends up pointing to a Window object instead of a LongPoll object.
    // Create this closure to pass into setTimeout to resolve the issue.
    var CreateRetryFunction = function(aLongPoll)
    {
        return function() {
            aLongPoll.SendCreate();
        }
    }

    var LongPoll = function(aCallbackStarted, aCallbackSuccess, aCallbackFailure)
    {
        this.kRetryTimeoutMs = 1000;
        this.kSessionIdStart = 0
        this.kSessionIdInvalid = Number.MAX_SAFE_INTEGER;
        this.iSessionId = this.kSessionIdStart;
        this.iCallbackStarted = aCallbackStarted;
        this.iCallbackSuccess = aCallbackSuccess;
        this.iCallbackFailure = aCallbackFailure;



        this.EStates = {
            eCreate : "initialising long polling",
            eLongPoll: "performing long polling",
            eTerminate: "terminating long polling",
        };
    }

    LongPoll.CreateLongPollRequest = function(aLongPoll)
    {
        var request = new HttpRequest();
        // An alternative to observing all onreadystatechange callbacks and
        // filtering would be to observe onerror and onload callbacks.
        // Note: must not mix the two approaches, as onreadystatechange receives callbacks for all events.
        request.SetOnReadyStateChange(CreateResponseCallback(aLongPoll, request));
        return request;
    }

    LongPoll.prototype.Terminate = function()
    {
        if (this.iSessionId !== this.kSessionIdStart
            && this.iSessionId !== this.kSessionIdInvalid) {
            this.SendTerminate();
            this.iSessionId = this.kSessionIdInvalid;
        }
    }

    LongPoll.prototype.ConstructSessionId = function()
    {
        var sessionId = "session-id: "+this.iSessionId;
        return sessionId;
    }

    LongPoll.prototype.SendSessionId = function(aRequest)
    {
        var sessionId = this.ConstructSessionId();
        aRequest.SetRequestHeader("Content-type", "text/plain");
        //aRequest.SetRequestHeader("Connection", "close");
        aRequest.Send(sessionId+"\r\n");
    }

    LongPoll.prototype.SendCreate = function()
    {
        console.log(">LongPoll.SendCreate\n")
        var request = LongPoll.CreateLongPollRequest(this);
        // FIXME - need to send URI prefix here
        request.Open("POST", "lpcreate", true);
        try {
            request.Send()
            console.log("LongPoll.SendCreate Request sent\n")
        }
        catch (err) { // InvalidStateError
            // Failure; retry.
            // FIXME - pass error up and have something else retry?
            console.log("LongPoll.SendCreate Request failed. Retrying.\n")
            setTimeout(CreateRetryFunction(this), this.kRetryTimeoutMs);
        }
    }

    LongPoll.prototype.SendTerminate = function(aAsynchronous)
    {
        // This should only be called when a browser tab closes.
        // Therefore, can't rely on asynchronous requests, so use a synchronous request.
        var request = LongPoll.CreateLongPollRequest(this);
        request.Open("POST", "lpterminate", aAsynchronous); // "false" makes request synchronous
        this.SendSessionId(request);
    }

    LongPoll.prototype.SendPoll = function()
    {
        console.log("LongPoll.SendPoll\n");
        var request = LongPoll.CreateLongPollRequest(this);
        request.Open("POST", "lp", true);
        this.SendSessionId(request);
    }

    LongPoll.prototype.SendUpdate = function(aString, aCallbackResponse, aCallbackError)
    {
        console.log("LongPoll.SendUpdate " + aString);
        var request = new HttpRequest();
        var sessionId = this.ConstructSessionId();

        var Response = function(aLongPoll) {
            if (aLongPoll.iSessionId == aLongPoll.kSessionIdInvalid) {
                console.log("Invalid session ID (response arrived after session terminated). Notifying upper layer of success.");
                aCallbackResponse(aString, "");
                return;
            }
            if (request.ReadyState() == 4) {
                if (request.Status() == 200) {
                    aCallbackResponse(aString, request.ResponseText());
                }
                else {
                    // Covers status of 0, i.e., network issues.
                    aCallbackError(aString, request.ResponseText(), request.Status());
                }
            }
            else if (request.ReadyState() == 0) {
                // Unable to send request for some reason.
                aCallbackError(aString, request.ResponseText(), request.Status());
            }
        }

        var CreateResponseCallback = function(aLongPoll)
        {
            return function() {
                Response(aLongPoll);
            }
        }

        request.SetOnReadyStateChange(CreateResponseCallback(this));
        request.Open("POST", "update", true);
        request.SetRequestHeader("Content-type", "text/plain");
        //request.setRequestHeader("Connection", "close");
        request.Send(sessionId+"\r\n"+aString+"\r\n");
    }

    LongPoll.prototype.Start = function()
    {
        this.SendCreate();
    }

    LongPoll.prototype.Restart = function(aWaitMs)
    {
        console.log("LongPoll.Restart this.iSessionId: " + this.iSessionId + " this.kSessionIdInvalid " + this.kSessionIdInvalid);
        if (this.iSessionId !== this.kSessionIdInvalid) {
            var asynchronous = true;
            this.SendTerminate(asynchronous);
            this.iSessionId = this.kSessionIdStart;
        }

        // Delay before trying to reconnect.
        setTimeout(CreateRetryFunction(this), aWaitMs);
    }

    LongPoll.prototype.ParseResponse = function(aResponse)
    {
        var parseErr = "Unable to parse JSON";
        if (aResponse == "") {
            this.iCallbackSuccess(aResponse);
        }
        else {
            try {
                var json = JSON.parse(aResponse);
                if (!json) {
                    throw parseErr;
                }
                this.iCallbackSuccess(json);
            }
            catch (err) {
                throw parseErr;
            }

        }
    }

    LongPoll.prototype.ProcessResponse = function(aRequest)
    {
        // A Terminate() call could be made in the period between a longpoll
        // being sent and its response being received.
        // In that case, the terminate call will have reset the state to
        // eCreate. If long polling fails, it will also fall back to being in
        // the eCreate state until a new session is established.

        if (this.iSessionId == this.kSessionIdInvalid) {
            // Not an active session, so don't process this response or call any handlers.
            return;
        }

        if (aRequest != null) {
            if (aRequest.ReadyState() == 4) {
                if (aRequest.Status() != 200) {
                    // Response was not OK.
                    this.ResponseFailure(aRequest); // Handles retry.
                    return;
                }

                var lines = aRequest.ResponseText().split("\r\n");
                var request = lines[0];

                if (request == 'lpcreate') {
                    var session = lines[1].split(":");
                    if (session.length == 2) {
                        var sessionVal = session[1].split(" ");
                        if (session[0] == "session-id" && sessionVal.length == 2) {
                            this.iSessionId = parseInt(sessionVal[1].trim());
                            this.iCallbackStarted();
                            this.SendPoll();
                            return;
                        }
                    }
                }
                else if (request == 'lp') {
                    // FIXME - check session ID?
                    // Split string after request line, as the response (i.e., any JSON) may contain newlines.
                    var json = aRequest.ResponseText().substring(lines[0].length+2);    // +2 to account for stripped \r\n
                    try {
                        this.ParseResponse(json);
                        console.log("LongPoll.ProcessResponse sending next lp request\n");
                        this.SendPoll();
                        return;
                    }
                    catch (err) {
                        console.log("LongPoll.ProcessResponse " + err + ". Trying to re-establish session");
                        // FIXME - as web page is no longer usable at this point (as long polls have been terminated),
                        // replace with a custom error page (that encourages user to reload, and/or also trigger a probe // request that will attempt to reload the page if the user doesn't manually reload)?
                    }
                }
                else if (request == 'lpterminate') {
                    // Session has been ended. Don't attempt to send anything futher.
                    return;
                }
                // Everything falls through to here if invalid response.
                //setTimeout(CreateRetryFunction(this), this.kRetryTimeoutMs);
            }
            else if (aRequest.ReadyState() === 0) {
                // Error.
                this.ResponseFailure(aRequest); // Handles retry.
            }
            else {
                // AJAX request readyState iterates from 1..4 as it is processed.
                // If state is not yet 4, it is not ready to be handled here.
            }
        }
        else {
            //setTimeout(CreateRetryFunction(this), this.kRetryTimeoutMs);
        }
    }

    LongPoll.prototype.ResponseFailure = function()
    {
        this.iCallbackFailure();
        console.log("LongPoll.ResponseFailure");
        setTimeout(CreateRetryFunction(this), this.kRetryTimeoutMs);
    }

    return {
        /**
         * Start AJAX long polling. Should be set as the onload() event by
         * client code.
         *
         * Parameter aUpdateCallback is a function taking a string as an
         * argument. Called when an update is received from server.
         * Parameter aFailureCallback is a function taking no arguments. Called
         * when long polling connection with server is lost. Allows clients to
         * provide some visibility of polling failure to clients.
         */
        StartLongPolling: function(aStartedCallback, aUpdateCallback, aFailureCallback)
        {
            if (aUpdateCallback == undefined) {
                alert("Error: WebUi.StartLongPolling(): aUpdateCallback is " + aUpdateCallback);
            }
            if (aFailureCallback == undefined) {
                alert("Error: WebUi.StartLongPolling(): aFailureCallback is " + aFailureCallback);
            }
            if (gStarted == true) {
                alert("Error: WebUi.StartLongPolling(): long polling already active");
                return;
            }
            gStarted = true;
            gLongPoll = new LongPoll(aStartedCallback, aUpdateCallback, aFailureCallback);
            gLongPoll.Start();
        },

        /**
         * Terminate AJAX long polling. Should be set as the onunload() event
         * by client code.
         */
        EndLongPolling: function()
        {
            if (gLongPoll == null) {
                alert("Error: WebUi.EndLongPolling(): StartLongPolling() must have been called prior to EndLongPolling()");
            }

            if (gStarted == false) {
                alert("Error: WebUi.EndLongPolling(): long polling is not active");
                return;
            }
            var asynchronous = false;
            gLongPoll.Terminate(asynchronous);
            gStarted = false;
        },

        RestartLongPolling: function()
        {
            if (gLongPoll == null) {
                alert("Error: WebUi.RestartLongPolling(): StartLongPolling() must have been called prior to RestartLongPolling()");
            }
            gLongPoll.Restart(5000);
        },

        /**
         * Send data from browser to server.
         *
         * param aString:           String of a user-defined format.
         * param aCallbackResponse: Response callback function of form CallbackResponse(aStringSent, aStringReceived).
         * param aCallbackError:    Error callback function of form CallbackError(aStringSent).
         * returns:                 null.
         */
        SendUpdateToServer: function(aString, aCallbackResponse, aCallbackError)
        {
            if (gLongPoll == null) {
                alert("Error: WebUi.SendUpdateToServer(): StartLongPolling() has not been called");
                return;
            }
            if (aCallbackResponse == undefined) {
                alert("Error: WebUi.SendUpdateToServer(): aCallbackResponse is " + aCallbackResponse);
                return;
            }
            if (aCallbackError == undefined) {
                alert("Error: WebUi.SendUpdateToServer(): aCallbackError is " + aCallbackError);
                return;
            }
            gLongPoll.SendUpdate(aString, aCallbackResponse, aCallbackError);
        }
    };

}(); // WebUi
