#!/bin/bash
# http://electron.mit.edu/~gsteele/ffmpeg/
for f in *ppm ; do convert -quality 100 $f `basename $f ppm`jpg; done 
mencoder "mf://*.jpg" -mf fps=25 -o video.avi -ovc lavc -lavcopts vcodec=msmpeg4v2:vbitrate=8000
