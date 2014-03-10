/**
 * 
 */
package cse101_proj_part2;

import java.util.ArrayList;

public class RandomPointset{
	private ArrayList<DoublePoint> rps = new ArrayList<DoublePoint>();
	int n = 0;
	
	RandomPointset(int n){
		this.n = n;
	}
	
	DoublePoint getPoint(){
		Double t = 2 * Math.PI * Math.random();
		Double u = 2 * Math.random();
		Double r = u > 1? (2-u):u;
		DoublePoint p = new DoublePoint(r * Math.cos(t), r * Math.sin(t));
		return p;
	}
	
	ArrayList<DoublePoint> getPointSet(){
		ArrayList<DoublePoint> rps = new ArrayList<DoublePoint>();
		
		for(int i = 0; i < n; i++){
			rps.add(getPoint());
		}
		
		return rps;
	}
	
	
}
