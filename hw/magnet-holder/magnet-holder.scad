$fn=100;
cylinder(d=30.5, h=2);
translate([0,0,6])difference(){union(){translate([0,0,-2])cube([8,8,4],center=true);
    translate([0,0,0]) rotate([90,0,0]) cylinder(d=8,h=8,center=true);}
    rotate([90,0,0])cylinder(d=4.6, h=20,center=true);
    };
    
translate([40,0,0]){
    difference(){cylinder(d=31+1.6,h=10.2);
        translate([0,0,0.2])cylinder(d=31,h=20);
    }
    }