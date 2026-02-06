#!/bin/sh
. "${srcdir=.}/init.sh"; path_prepend_ ../src

echo 'hello
helllo
hullo
helllloo
yelloo
jello
help' > input.txt

cat > expected.out <<EOF
hello
helllo
hullo
yelloo
jello
help
EOF

grep --approx=2 hello input.txt > actual.out || fail_ "grep failed"
compare actual.out expected.out || fail_ "output mismatch"
Exit 0
