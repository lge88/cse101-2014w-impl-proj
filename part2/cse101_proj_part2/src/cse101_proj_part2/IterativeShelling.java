package cse101_proj_part2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class IterativeShelling {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		//int[] n = {20,50,100,200,500,1000,2000,3000};
		int[] n = {20,50};
		ArrayList<Integer> result = new ArrayList<Integer>();
		ArrayList<DoublePoint> rps = null;
		ArrayList<DoublePoint> hull = new ArrayList<DoublePoint>();
		ConvexHullAlgorithm cha = null;
		
		for (int i = 0; i < n.length; i++){
			rps = new RandomPointset(n[i]).getPointSet();
			rps.add(new DoublePoint(2.5,2.5));
			rps.add(new DoublePoint(2.5,-2.5));
			rps.add(new DoublePoint(-2.5,2.5));
			rps.add(new DoublePoint(-2.5,-2.5));
			cha = new ConvexHullAlgorithm(rps);
			cha.setCurrentPointSet(rps);
			
			int j = 1;
			hull.addAll(cha.getHull());
			rps = cha.getCurrentPointSet();
			while(rps.size()!=0){
				j++;
				hull.addAll(cha.getHull());
				rps = cha.getCurrentPointSet();
				try {
					 
					//String content = "This is the content to write into file";
		 
					File file = new File("C:/Users/SKY/Dropbox/1_UCSD/CSE101/Homework/hull"+i+" "+j+".txt");
		 
					// if file doesnt exists, then create it
					if (!file.exists()) {
						file.createNewFile();
					}
		 
					FileWriter fw = new FileWriter(file.getAbsoluteFile());
					BufferedWriter bw = new BufferedWriter(fw);
					for(DoublePoint p : hull){
						bw.write(p.getX()+" "+p.getY()+"\n");
					}
					bw.close();
		 
					System.out.println("Done1");
					
					File file2 = new File("C:/Users/SKY/Dropbox/1_UCSD/CSE101/Homework/pointsets"+i+" "+j+".txt");
					 
					// if file doesnt exists, then create it
					if (!file2.exists()) {
						file2.createNewFile();
					}
		 
					FileWriter fw2 = new FileWriter(file2.getAbsoluteFile());
					BufferedWriter bw2 = new BufferedWriter(fw2);
					for(DoublePoint p : rps){
						bw2.write(p.getX()+" "+p.getY()+" \n");
					}
					bw2.close();
		 
					System.out.println("Done2");
		 
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			
			//write to file
			
			result.add(j);
		}
		
		//get points info
		
		//new WriteFile("C:\Users\SKY\Dropbox\1_UCSD\CSE101\Homework\hull",hull)
		
		//get mean
		
		//get deviation
		
		

	}

}
