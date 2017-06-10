$fn=40;
color([1,0,0]) colorbox();
color([0,0,1]) topcone();
lid();

module colorbox(){
    difference(){union(){
    basebox();
    translate([(28.4-3.2)/2,(28.7-3.2)/2,3/2])cylinder(d=6,h=3,center=true);
    translate([(28.4-3.2)/2,-(28.7-3.2)/2,3/2])cylinder(d=6,h=3,center=true);
    translate([-(28.4-3.2)/2,(28.7-3.2)/2,3/2])cylinder(d=6,h=3,center=true);
    translate([-(28.4-3.2)/2,-(28.7-3.2)/2,3/2])cylinder(d=6,h=3,center=true);
    }
    translate([(28.4-3.2)/2,(28.7-3.2)/2,2])cylinder(d=2.4,h=5,center=true);
    translate([(28.4-3.2)/2,-(28.7-3.2)/2,2])cylinder(d=2.4,h=5,center=true);
    translate([-(28.4-3.2)/2,(28.7-3.2)/2,2])cylinder(d=2.4,h=5,center=true);
    translate([-(28.4-3.2)/2,-(28.7-3.2)/2,2])cylinder(d=2.4,h=5,center=true);
    translate([0,-(28.7-3.2)/2,0])cube([14,3,4],center=true);
    translate([0,(28.7-3.2)/2,0])cube([14,3,4],center=true);
    }
}


module lid(){
difference(){translate([-100+8,-48/2,0])import("bb-sen-uni-bt-c.stl");
    cylinder(h=20,d=32);
    translate([0,-20,(8-1.2)/2-0.205])cube([25,10,8-1.2],center=true);
    cylinder(d=36,h=7.1);
    }
}
    
module topcone(){
    intersection(){
    translate([0,0,5])difference()
    {union(){
        translate([0,0,0.45])cylinder(d=34,h=0.9,center=true);
        translate([0,0,25.25/2])cylinder(d=31,h=24+1.25,center=true);
        }
        translate([0,0,25.25/2])cylinder(d=31-2.4,h=24+1.25+0.2,center=true);
        }
        linear_extrude(height=400)scale([0.95,0.95,1])translate([-56/2,-48/2,0])import("molebox.dxf",layer="innerbox");
    }
    }
module basebox(){
    translate([-56/2,-48/2,0])difference(){linear_extrude(height=8) import("molebox.dxf",layer="0",convexity=10);
translate([0,0,1.25])linear_extrude(height=8) import("molebox.dxf",layer="innerbox");
translate([0,0,6.35])linear_extrude(height=8) import("molebox.dxf",layer="lid",convexity=10);
    translate([4,4,4]) doublehole();
    translate([4,4+16,4]) doublehole();
    translate([4,4+40,4]) doublehole();
    translate([4+48,4,4]) doublehole();
    translate([4+48,4+16,4]) doublehole();
    translate([4+48,4+40,4]) doublehole();
    translate([4+16,4+48,4]) rotate([0,0,90])doublehole();
    translate([4+32,4+48,4]) rotate([0,0,90])doublehole();
        translate([10,4+8,6.35-1.5]) cube([1.2,5.7,0.9],center=true);
        translate([10,4+28,6.35-1.5]) cube([1.2,5.7,0.9],center=true);
        translate([46,4+8,6.35-1.5]) cube([1.2,5.7,0.9],center=true);
        translate([46,4+28,6.35-1.5]) cube([1.2,5.7,0.9],center=true);
        translate([56/2,56-10,6.35-1.5]) cube([5.7,1.2,0.9],center=true);
    }
}
module doublehole(){
    union(){
        cylinder(d=4.8,h=9,center=true);
        rotate([90,0,0])cylinder(d=4.8,h=9,center=true);
        }
        }