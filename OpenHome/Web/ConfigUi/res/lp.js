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

    var CreateFailureCallback = function(aLongPoll, aRequest)
    {
        return function() {
            aLongPoll.ResponseFailure(aRequest);
        }
    }

    var LongPoll = function(aCallbackStarted, aCallbackSuccess, aCallbackFailure)
    {
        this.iSessionId = 0;    // 0 == invalid
        this.iCallbackStarted = aCallbackStarted;
        this.iCallbackSuccess = aCallbackSuccess;
        this.iCallbackFailure = aCallbackFailure;
        this.EStates = {
            eCreate : "initialising long polling",
            eLongPoll: "performing long polling",
            eTerminate: "terminating long polling",
        };
        this.iState = this.EStates.eCreate;
        //this.iState = this.EStates.eLongPoll;
    }

    LongPoll.CreateLongPollRequest = function(aLongPoll)
    {
         var request = new HttpRequest();
         request.SetOnReadyStateChange(CreateResponseCallback(aLongPoll, request));
         request.AddEventListener("error", CreateFailureCallback(aLongPoll, request), false);
         return request;
    }

    LongPoll.prototype.Terminate = function()
    {
        if (this.iSessionId != 0) {
            this.SendTerminate();
            this.iSessionId = 0;
            // this.iState = this.EStates.eCreate;
            this.iState = this.EStates.eTerminate;
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
        var request = LongPoll.CreateLongPollRequest(this);
        // FIXME - need to send URI prefix here
        // FIXME - what if we don't get a response to this?
        // - need a timeout for each request so we can resend
        request.Open("POST", "lpcreate", true);
        try {
            request.Send()
        }
        catch (err) { // InvalidStateError
            // If InvalidStateError, aRequest was not opened.
            // Try calling SendCreate() again.
            // FIXME - delay for 5s first?
            this.SendCreate();
        }
    }

    LongPoll.prototype.SendTerminate = function()
    {
        // This should only be called when a browser tab closes.
        // Therefore, can't rely on asynchronous requests, so use a synchronous request.
        var request = LongPoll.CreateLongPollRequest(this);
        request.Open("POST", "lpterminate", false); // "false" makes request synchronous
        this.SendSessionId(request);
    }

    LongPoll.prototype.SendPoll = function()
    {
        var request = LongPoll.CreateLongPollRequest(this);
        request.Open("POST", "lp", true);
        this.SendSessionId(request);
    }

    LongPoll.prototype.SendUpdate = function(aString, aCallbackResponse, aCallbackError)
    {
        var request = new HttpRequest();
        var sessionId = this.ConstructSessionId();

        Response = function() {
            if (request.ReadyState() == 4) {
                if (request.Status() == 200) {
                    aCallbackResponse(aString, request.ResponseText());
                }
                else {
                    aCallbackError(aString);
                }
            }
        }

        ResponseError = function() {
            aCallbackError(aString);
        }

        request.SetOnReadyStateChange(Response);
        request.AddEventListener("error", ResponseError, false);
        request.Open("POST", "update", true);
        request.SetRequestHeader("Content-type", "text/plain");
        //request.setRequestHeader("Connection", "close");
        request.Send(sessionId+"\r\n"+aString+"\r\n");
    }

    LongPoll.prototype.Start = function()
    {
        this.SendCreate();
    }

    LongPoll.prototype.ParseResponse = function(aResponse)
    {
        if (aResponse == "") {
            this.iCallbackSuccess(aResponse);
        }
        else {
            try {
                var json = JSON.parse(aResponse);
                if (!json) {
                    throw "Unable to parse JSON";
                }
                for (var i=0; i<json.length; i++) {
                    this.iCallbackSuccess(json[i]);
                }
            }
            catch (err) {
                alert("Error: LongPoll.ParseResponse could not parse JSON response");
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
        var session = null;
        var sessionVal = null;
        // if (this.iState == this.EStates.eTerminate) {
            // return;
        // }
        // else if (aRequest.status == 0) {
            // this.SendCreate();
        // }

        if (aRequest == null || aRequest.ReadyState() != 4) {
            return;
        }

        var lines = aRequest.ResponseText().split("\r\n");
        var request = lines[0]

        if (this.iState == this.EStates.eTerminate && request == "lpcreate") {
            if (aRequest.ReadyState()==4 && aRequest.Status()==200) {
                this.iState = this.EStates.eTerminate;
                location.reload();  // re-established connection; reload page
                // FIXME - reloading page here means long polling connection will be destroyed and re-established again
            }
        }

        if (request == "lpcreate" || request == 'lp') {
            if (aRequest.ReadyState()==4 && aRequest.Status()==200) {
                if (request == 'lpcreate') {
                    session = lines[1].split(":");
                    if (session.length == 2) {
                        sessionVal = session[1].split(" ");
                        if (session[0] == "session-id" && sessionVal.length == 2) {
                            this.iSessionId = parseInt(sessionVal[1].trim());
                            this.iState = this.EStates.eLongPoll;
                            this.iCallbackStarted();
                            this.SendPoll();
                            return;
                        }
                    }
                    this.SendCreate();
                }
                else { // request == lp
                    // FIXME - check session ID?
                    // Split string after request line, as the response (i.e., any JSON) may contain newlines.
                    var json = aRequest.ResponseText().substring(lines[0].length+2);    // +2 to account for stripped \r\n
                    this.ParseResponse(json);
                    // FIXME - should delay for 5s
                    this.SendPoll();
                }
            }
            else if (aRequest.Status() == 0) {
                this.SendCreate();
            }
        }
        else { // some other URL unrelated to longpolling
        }
        // else {
            // alert("Error: WebUi.LongPoll.MakeNextPollCall() unknown iState: "+this.iState);
        // }
    }

    LongPoll.prototype.ResponseFailure = function()
    {
        this.iCallbackFailure();
        this.iState = this.EStates.eTerminate;
        this.SendCreate();  // FIXME - is calling this after response code above calling SendCreate() causing the request to abort on Open()?
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
            gLongPoll.Terminate();
            // FIXME - how to hook this into MakeNextPollCall()?
            gStarted = false;
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
