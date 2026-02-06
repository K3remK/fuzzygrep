#!/bin/sh
. "${srcdir=.}/init.sh"; path_prepend_ ../src

echo 'halo
helllo
hullo
mellow
world' > input.txt

cat > expected.out <<EOF
EOF

grep --approx=0 hello input.txt > actual.out || fail_ "grep failed"
compare actual.out expected.out || fail_ "output mismatch"
Exit 0
