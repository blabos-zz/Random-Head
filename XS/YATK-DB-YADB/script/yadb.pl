#!/usr/bin/perl

use FindBin;
use lib "$FindBin::Bin/../lib";

use strict;
use warnings;

use blib;
use YATK::DB::YADB qw{:all};
use Data::Dumper;

my $dbfile = defined $ARGV[0] ? $ARGV[0] : 'data.ydb';

init($dbfile);
load();
dump();

my $record = get('3');
if (defined $record) {
    print Dumper($record), $/;
    print 'KEY: ', $record->{'key'}, $/;
    print 'VAL: ', $record->{'val'}, $/;
}

my @list = range(1,6,3);

foreach (@list) {
    print 'List: ', $_, $/;
}
