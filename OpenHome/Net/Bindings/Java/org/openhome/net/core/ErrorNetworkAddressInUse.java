package org.openhome.net.core;

/**
 * Thrown when initialisation fails due to an attempt to reuse a network address.
 *
 * <p>This may imply that another similarly configured instance of ohNet is already running.
 * On Windows, it could also mean that too many instances of ohNet have been recently launched.
 */
public class ErrorNetworkAddressInUse extends RuntimeException
{
}
