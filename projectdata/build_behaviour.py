# Defines the build behaviour for continuous integration builds.
#
# Invoke with "go hudson_build"

# Maintenance notes:
#
# The following special functions are available for use in this file:
#
# add_option("-t", "--target", help="Set the target.")
#     Add a command-line option. See Python's optparse for arguments.
#     options are accessed on context.options. (See build_step.)
#
# fetch_dependencies("ohnet", "nunit", "zwave", platform="Linux-ARM")
# fetch_dependencies(["ohnet", "log4net"], platform="Windows-x86")
#     Fetches the specified dependencies for the specified platform. Omit platform
#     to use the platform defined in the OH_PLATFORM environment variable.
#
# get_dependency_args("ohnet", "nunit", "zwave")
# get_dependency_args(["ohnet", "log4net"])
#     Returns a list of the arguments found in the dependencies.txt file
#     for the given dependencies, using the current environment.
#
# @build_step("name", optional=True, default=False)
# @build_condition(OH_PLATFORM="Linux-x86")
# @build_condition(OH_PLATFORM="Windoxs-x86")
# def your_build_step(context):
#     ...
#     Add a new build-step that only runs when one of the build conditions
#     matches. (Here if OH_PLATFORM is either "Linux-x86" or "Windows-x86".)
#     Context will be an object with context.options and context.env defined.
#     Name argument is optional and defaults to the name of the function. If
#     optional is set to True you can enable or disable the step with
#     select_optional_steps, and default determines whether it will run by
#     default.
#
# select_optional_steps("+build", "-test")
# select_optional_steps("stresstest", disable_others=True)
#     Enables or disables optional steps. Use "+foo" to enable foo, and "-foo"
#     to disable it. Use 'disable_others=True' to disable all optional steps
#     other than those specifically enabled.
#
# python("waf", "build")
#     Invoke a Python subprocess. Provide arguments as strings or lists of
#     strings.
#
# rsync(...)
#     Invoke an rsync subprocess. See later for examples.
#
# shell(...)
#     Invoke a shell subprocess. Arguments similar to python().
#
# with SshSession(host, username) as ssh:
#     ssh("echo", "hello")
#
#     Connect via ssh and issue commands. Command arguments similar to python().
#  

from ci import (
        build_step, require_version, add_option, specify_optional_steps,
        build_condition, default_platform, get_dependency_args,
        get_vsvars_environment, fetch_dependencies, python, scp)

require_version(22)


# Command-line options. See documentation for Python's optparse module.
add_option("-t", "--target", help="Target platform.")
add_option("-a", "--artifacts", help="Build artifacts directory. Used to fetch dependencies.")
add_option("--debug", action="store_const", const="Debug", dest="debugmode", default="Debug", help="Build debug version.")
add_option("--release", action="store_const", const="Release", dest="debugmode", help="Build release version.")
add_option("--steps", default="default", help="Steps to run, comma separated. (all,default,fetch,configure,build,bundle,tests,publish)")
add_option("--publish-version", action="store", help="Specify version string.")
add_option("--fetch-only", action="store_const", const="fetch", dest="steps", help="Fetch dependencies only.")

@build_step()
def choose_optional_steps(context):
    specify_optional_steps(context.options.steps)

# Unconditional build step. Choose a platform and set the
# appropriate environment variable.
@build_step()
def choose_platform(context):
    if context.options.target:
        context.env["OH_PLATFORM"] = context.options.target
    elif "PLATFORM" in context.env:
        context.env["OH_PLATFORM"] = {
                "Windows-x86" : "Windows-x86",
                "Windows-x64" : "Windows-x64",
                "Linux-x86" : "Linux-x86",
                "Linux-x64" : "Linux-x64",
                "Linux-ARM" : "Linux-ARM",
                "Linux-ppc32" : "Linux-ppc32",
                "Macos-x64" : "Mac-x64",
                "Core-ppc32" : "Core-ppc32",
                "Core-armv5" : "Core-armv5",
                "Core-armv6" : "Core-armv6",
            }[context.env["PLATFORM"]]
    else:
        context.env["OH_PLATFORM"] = default_platform()

# Universal build configuration.
@build_step()
def setup_universal(context):
    env = context.env
    env.update(
        OH_PUBLISHDIR="artifacts@core.linn.co.uk:/home/artifacts/public_html/artifacts/",
        OH_PROJECT="ohMediaPlayer",
        OH_DEBUG=context.options.debugmode,
        BUILDDIR='buildhudson',
        WAFLOCK='.lock-wafbuildhudson',
        OH_VERSION=context.options.publish_version or context.env.get('RELEASE_VERSION', 'UNKNOWN'))
    context.configure_args = get_dependency_args(env={'debugmode':env['OH_DEBUG']})
    context.configure_args += ["--dest-platform", env["OH_PLATFORM"]]
    context.configure_args += ["--" + context.options.debugmode.lower()]

# Extra Windows build configuration.
@build_step()
@build_condition(OH_PLATFORM="Windows-x86")
@build_condition(OH_PLATFORM="Windows-x64")
def setup_windows(context):
    env = context.env
    env.update(
        OPENHOME_NO_ERROR_DIALOGS="1",
        OHNET_NO_ERROR_DIALOGS="1")
    env.update(get_vsvars_environment())

# Extra Linux build configuration.
@build_step()
@build_condition(OH_PLATFORM="Linux-x86")
@build_condition(OH_PLATFORM="Linux-x64")
@build_condition(OH_PLATFORM="Linux-ARM")
@build_condition(OH_PLATFORM="Linux-ppc32")
def setup_linux(context):
    env = context.env

# Principal build steps.
@build_step("fetch", optional=True)
def fetch(context):
    fetch_dependencies(env={'debugmode':context.env['OH_DEBUG']})

@build_step("configure", optional=True)
def configure(context):
    python("waf", "configure", context.configure_args)

@build_step("clean", optional=True)
def clean(context):
    python("waf", "clean")

@build_step("build", optional=True)
def build(context):
    python("waf", "build")

@build_step("bundle", optional=True)
def bundle(context):
    python("waf", "bundle")

@build_step("test", optional=True)
def test(context):
    python("waf", "test")

@build_step("test_full", optional=True, default=False)
def test_full(context):
    python("waf", "test_full")

@build_step("publish", optional=True, default=False)
def publish(context):
    targetpath    = "{OH_PUBLISHDIR}/{OH_PROJECT}/{OH_PROJECT}-{OH_VERSION}-{OH_PLATFORM}-{OH_DEBUG}.tar.gz".format(**context.env)
    sourcepath    = "{BUILDDIR}/{OH_PROJECT}.tar.gz".format(**context.env)
    scp(sourcepath,    targetpath)
