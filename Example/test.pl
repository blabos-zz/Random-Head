#!/usr/bin/perl -Iblib -Ilib

use blib;
use Example ':all';

use Data::Dumper;

init('database.ydb');
load();
dump();
$res = get('3');

if (defined $res) {
    print Dumper($res), $/;
}
else {
    print 'UNDEF', $/;
}