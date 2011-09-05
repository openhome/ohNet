using System;

namespace OpenHome.Net.Device
{
    /// <summary>
    /// Thrown when an action with no registered delegate is invoked.  Will not be visible to external code
    /// </summary>
    public class ActionDisabledError : Exception
    {
    }

    /// <summary>
    /// Thrown when an invoked action fails.  Will not be visible to external code
    /// </summary>
    public class ActionError : Exception
    {
        public ActionError()
        {
        }
        public ActionError(string aMessage)
            : base(aMessage)
        {
        }
        public ActionError(string aMessage, int aCode)
            : base(String.Format("{0}: {1}", aCode, aMessage))
        {
        }
    }

    /// <summary>
    /// Thrown when an attempt is made to update a property to a value not in the AllowedValues range/set
    /// </summary>
    public class PropertyUpdateError : Exception
    {
    }
}
