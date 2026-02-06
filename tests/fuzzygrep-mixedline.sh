#!/bin/sh
. "${srcdir=.}/init.sh"; path_prepend_ ../src

echo 'foo helllo bar
baz hullo qux
hello
no-match-line
one-more-jello' > input.txt

cat > expected.out <<EOF
foo helllo bar
baz hullo qux
hello
one-more-jello
EOF

grep --approx=1 hello input.txt > actual.out || fail_ "grep failed"
compare actual.out expected.out || fail_ "output mismatch"
Exit 0
