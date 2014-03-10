package cse101_proj_part2;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class ConvexHullAlgorithm
{
	ArrayList<DoublePoint> ps = new ArrayList<DoublePoint>();
	ArrayList<DoublePoint> hull = null;
	
	public ConvexHullAlgorithm(ArrayList<DoublePoint> ps){
		this.ps = ps;
		this.hull = new ArrayList<DoublePoint>();
	}
	
	ArrayList<DoublePoint> getHull(){
		if (this.ps!=null){
			if (this.ps.size()>2)
				hull = this.execute(ps);
			else
				hull = this.ps;
			//System.out.println("executed!");
			}
		if(hull==null){
			System.out.println("ao");
		}
		return this.hull;
	}

	ArrayList<DoublePoint> getCurrentPointSet(){
		
		ArrayList<DoublePoint> currentPs = new ArrayList<DoublePoint>();
		//System.out.println(this.hull.size()+"1");
		for (DoublePoint p : this.ps){
			if (this.hull.contains(p)){
				
				//System.out.println("added!");
			}else{
				currentPs.add(p);
			}
			//System.out.println(currentPs.size()+" currentPs.size()");
	
		}
		setCurrentPointSet(currentPs);
		return currentPs;
	}
	
	void setCurrentPointSet(ArrayList<DoublePoint> ps){
		this.ps = ps;
		//System.out.println(this.ps.size()+" ps size");
	}
	
	//// this returns the hull
        private ArrayList<DoublePoint> execute(ArrayList<DoublePoint> points) 
        {
                ArrayList<DoublePoint> xSorted = (ArrayList<DoublePoint>) points.clone();
                Collections.sort(xSorted,new XCompare());
                
                int n = xSorted.size();
                //System.out.println(n+" dododododo");
                DoublePoint[] lUpper = new DoublePoint[n];
                
                lUpper[0] = xSorted.get(0);
                lUpper[1] = xSorted.get(1);
                
               // System.out.println(lUpper[0].getX());
               // System.out.println(lUpper[1].getX());
                
                int lUpperSize = 2;
                
                for (int i = 2; i < n; i++)
                {
                        lUpper[lUpperSize] = xSorted.get(i);
                        lUpperSize++;
                        
                        while (lUpperSize > 2 && !rightTurn(lUpper[lUpperSize - 3], lUpper[lUpperSize - 2], lUpper[lUpperSize - 1]))
                        {
                                // Remove the middle point of the three last
                                lUpper[lUpperSize - 2] = lUpper[lUpperSize - 1];
                                lUpperSize--;
                        }
                }
                
                DoublePoint[] lLower = new DoublePoint[n];
                
                lLower[0] = xSorted.get(n - 1);
                lLower[1] = xSorted.get(n - 2);
                
                int lLowerSize = 2;
                
                for (int i = n - 3; i >= 0; i--)
                {
                        lLower[lLowerSize] = xSorted.get(i);
                        lLowerSize++;
                        
                        while (lLowerSize > 2 && !rightTurn(lLower[lLowerSize - 3], lLower[lLowerSize - 2], lLower[lLowerSize - 1]))
                        {
                                // Remove the middle point of the three last
                                lLower[lLowerSize - 2] = lLower[lLowerSize - 1];
                                lLowerSize--;
                        }
                }
                
                ArrayList<DoublePoint> result = new ArrayList<DoublePoint>();
                
                for (int i = 0; i < lUpperSize; i++)
                {
                        result.add(lUpper[i]);
                        //System.out.println(lUpper[i].getX()+" "+lUpper[i].getY());
                }
                
                for (int i = 1; i < lLowerSize - 1; i++)
                {
                        result.add(lLower[i]);
                        //System.out.println(lUpper[i].getX()+" "+lUpper[i].getY());
                }
                //System.out.println(result.size()+"e");
                return result;
        }
        
        private boolean rightTurn(DoublePoint a, DoublePoint b, DoublePoint c)
        {
                return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x) > 0;
        }

        private class XCompare implements Comparator<DoublePoint>{
        	public int compare(DoublePoint o1, DoublePoint o2) 
            {
                    if(o1.x > o2.x)
                    	return 1;
                    else if (o1.x < o2.x)
                    	return -1;
                    else return 0;
               
            }
        }
}