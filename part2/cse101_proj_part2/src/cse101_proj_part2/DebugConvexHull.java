package cse101_proj_part2;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class DebugConvexHull {

	/**
	 * @param args
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException {
		int n = 200;
		ArrayList<DoublePoint> points = new RandomPointset(n).getPointSet();
		ConvexHullAlgorithm cha = new ConvexHullAlgorithm(points);
		ArrayList<DoublePoint> hull = cha.getHull(); 
		
		PrintWriter ptsWriter = new PrintWriter("debug_results/points_" + n + ".txt");
		PrintWriter hullWriter = new PrintWriter("debug_results/hull_" + n + ".txt");
		
		for (DoublePoint p : points)
			ptsWriter.println(p.getX() + " " + p.getY());
		
		for (DoublePoint p : hull)
			hullWriter.println(p.getX() + " " + p.getY());
		
		ptsWriter.close();
		hullWriter.close();
	}

}
