#!/bin/sh
SCRIPT=`readlink -f $0`
PROJECT_ROOT=`dirname $SCRIPT`
# Force Python processes to be unbuffered. Avoids jumbled output
# during CI builds caused by buffering of stdout.
export PYTHONUNBUFFERED=x
if [ -z "$OHDEVTOOLS_ROOT" ]; then
  export OHDEVTOOLS_ROOT=`readlink -f $PROJECT_ROOT/ohdevtools`
fi
if [ ! -e "$OHDEVTOOLS_ROOT" ]; then
  export OHDEVTOOLS_ROOT=`readlink -f $PROJECT_ROOT/../ohdevtools`
fi
if [ ! -e "$OHDEVTOOLS_ROOT" ]; then
  echo OHDEVTOOLS_ROOT not set.
  echo Tried looking in $OHDEVTOOLS_ROOT.
  echo Please set OHDEVTOOLS_ROOT to point to the location of the ohdevtools scripts.
  exit 1
fi
if [ -z "$PYTHONPATH" ]; then
  export PYTHONPATH=$OHDEVTOOLS_ROOT
else
  export PYTHONPATH=$OHDEVTOOLS_ROOT:$PYTHONPATH
fi
cd "$PROJECT_ROOT"
python -u -m go $@
