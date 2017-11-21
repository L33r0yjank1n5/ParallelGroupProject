/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package addusergroups;

/**
 *
 * @author Aditya
 */
public class UserInfo {
    private String userID;
    private String productID;
    private double rating;
    private int someID;
    private String group;
    
    public UserInfo(){
        
    }
    
    public UserInfo(String userID, String productID, double rating, int someID, String group){
        this.userID = userID;
        this.productID = productID;
        this.rating = rating;
        this.someID = someID;
        this.group = group;
    }

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getProductID() {
        return productID;
    }

    public void setProductID(String productID) {
        this.productID = productID;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    public int getSomeID() {
        return someID;
    }

    public void setSomeID(int someID) {
        this.someID = someID;
    }

    public String getGroup() {
        return group;
    }

    public void setGroup(String group) {
        this.group = group;
    }
     
    @Override
    public String toString(){
        return "UserID: " + userID + " Rating: " + rating + "Group: " + group;
    }
}
