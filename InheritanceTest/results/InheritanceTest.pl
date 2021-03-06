use strict;
use warnings;

package BasePrinter;

sub new
{
    my $class = shift;
    my $self = {};
    bless $self, $class;
    $self->{num_value} = 42;
    return $self;
}

sub get_value {
    my ( $self ) = @_;
    return "Base";
}

sub print_it {
    my ( $self ) = @_;
    print(("BasePrinter: @{[$self->get_value()]}") . "\n");
}

sub some_base_func {
    my ( $self ) = @_;
    return $self->{num_value};
}

package ChildPrinter;

use parent -norequire, 'BasePrinter';

sub new
{
    my $class = shift;
    my $self = {};
    bless $self, $class;
    return $self;
}

sub get_value {
    my ( $self ) = @_;
    return "Child";
}

package TestClass;

sub new
{
    my $class = shift;
    my $self = {};
    bless $self, $class;
    return $self;
}

sub get_printer {
    my ( $self, $name ) = @_;
    my $result = $name eq "child" ? new ChildPrinter() : new BasePrinter();
    return $result;
}

sub test_method {
    my ( $self ) = @_;
    my $base_printer = $self->get_printer("base");
    my $child_printer = $self->get_printer("child");
    $base_printer->print_it();
    $child_printer->print_it();
    print(("@{[$base_printer->some_base_func()]} == @{[$child_printer->some_base_func()]}") . "\n");
    
    my $base_p2 = new BasePrinter();
    my $child_p2 = new ChildPrinter();
    print(("@{[$base_p2->{num_value}]} == @{[$child_p2->{num_value}]}") . "\n");
}

package Program;

eval {
    my $c = new TestClass();
    $c->test_method();
};
if ($@) {
    print "Exception: " . $@
}