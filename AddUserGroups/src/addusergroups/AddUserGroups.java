/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package addusergroups;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.nio.file.Path;

/**
 *
 * @author Aditya
 */
public class AddUserGroups {

    //Point to the desired csv
    private final static String fileNames = "C:\\Users\\Aditya\\Desktop\\ratings_Musical_Instruments.csv";
    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        
           
        List<UserInfo> userInfos = readUserInfoFromCSV(fileNames);
       // List<UserInfo> newUserInfo = new ArrayList<>();
        UserInfo user = new UserInfo();
        for (UserInfo b : userInfos) 
        {             
            if(Character.isDigit((b.getUserID().charAt(1))) && Character.isDigit((b.getUserID()).charAt(2))){
               b.setGroup("A");
               user.setGroup(b.getGroup());
            }
            else if(Character.isDigit((b.getUserID().charAt(1))) && Character.isLetter((b.getUserID()).charAt(2))){
               b.setGroup("B");
               user.setGroup(b.getGroup());
            }
            else if(Character.isLetter((b.getUserID().charAt(1))) && Character.isDigit((b.getUserID()).charAt(2))){
              b.setGroup("C");
              user.setGroup(b.getGroup());
            }
            else if(Character.isLetter((b.getUserID().charAt(1))) && Character.isLetter((b.getUserID()).charAt(2))){
              b.setGroup("D");
              user.setGroup(b.getGroup());
            }
        }
        
        createNewCSV(userInfos); 
    }
    
    private static List<UserInfo> readUserInfoFromCSV(String fileName) throws IOException{
        List<UserInfo> userInfos = new ArrayList<>();
        Path pathToFile = Paths.get(fileName);
        
        
        BufferedReader br = Files.newBufferedReader(pathToFile, StandardCharsets.US_ASCII);
        String line = br.readLine();
        while (line != null) {
                
            String[] attributes = line.split(",");
            UserInfo userInfo = createUser(attributes); 
            userInfos.add(userInfo); 
            line = br.readLine(); 
        } 
       
        return userInfos;
    }

    
     private static void createNewCSV(List<UserInfo> userInfo) throws IOException{
        PrintWriter pw = null;
        try {
            pw = new PrintWriter(new File("New_ratings_Musical_Instruments.csv")); //new name for file
        } catch (FileNotFoundException e) {
        }
        StringBuilder builder = new StringBuilder();
        for(UserInfo f : userInfo){
           
        builder.append(f.getUserID()).append(",");
        builder.append(f.getProductID()).append(",");
        builder.append(f.getRating()).append(",");
        builder.append(f.getSomeID()).append(",");
        builder.append(f.getGroup());
        builder.append('\n');
     }
        pw.write(builder.toString());
        pw.close();
        System.out.println("done!");
    }
    
    private static UserInfo createUser(String[] metadata){
        String userID = metadata[0];
        String productID = metadata[1];
        double rating = Double.parseDouble(metadata[2]);
        int someID = Integer.parseInt(metadata[3]);
        String group = metadata[4];
    
        return new UserInfo(userID, productID, rating, someID, group);
    }
    
}



