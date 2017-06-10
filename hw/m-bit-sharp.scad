$fn=50;
translate([0,-4,0])union(){
difference(){
    translate([0,4,0]) cube([48,16,8],center=true);
    translate([0,3,2.5]) cube([45.5,15,8],center=true);
    translate([-37/2,3.5,0]) cylinder(h=10,d=2,center=true);
    translate([37/2,3.5,0]) cylinder(h=10,d=2,center=true);
    //translate([0,-8,1.5]) cube([11,10,8],center=true);    
}
translate([-28,8,0])rotate([0,0,90])beam(1,1,true);
translate([-28,-8,0])rotate([0,0,90])beam(1,1,true);
translate([28,-8,0])rotate([0,0,90])beam(1,1,true);
translate([-16,-8,0])rotate([0,0,90])beam(1,2);
translate([16,-8,0])rotate([0,0,90])beam(1,2);
translate([28,8,0])rotate([0,0,90])beam(1,1,true);
translate([8,16,0])rotate([0,0,0])beam(1,1,true);
translate([-8,16,0])rotate([0,0,0])beam(1,1,true);
translate([0,-8,-1.5])cube([16,8,5],center=true);
}



module beam(width,height, horizontal=false){
    difference(){
        union(){
            cube([8*(width),8*height,8], center=true);
        }
        for(i=[-(8*(height/2+0.5)):8:(8*(height/2+0.5))])
            for(j=[-8*(width/2-0.5):8:(8*(width/2-0.5))])
                translate([j,i,0])cylinder(d=5,h=9,center=true);
        if(horizontal){
            for(i=[-(8*(height/2+0.5)):8:(8*(height/2+0.5))])
                for(j=[-8*(width/2-0.5):8:(8*(width/2-0.5))])
                    translate([j,i,0]) rotate([0,90,0])cylinder(d=5,h=9,center=true);
        }
    }
}