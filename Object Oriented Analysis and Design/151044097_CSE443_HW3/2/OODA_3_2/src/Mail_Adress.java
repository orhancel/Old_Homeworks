/**
 * Created by ORHAN on 10.12.2018.
 */
public class Mail_Adress {

    public String  adress;
    public String  owner_Name;

    public Mail_Adress(String ad,String owner){
        adress=ad;
        owner_Name=owner;
    }

    public void Display(){
        System.out.println("Mail adress: "+adress);
        System.out.println("Owner : "+owner_Name);
    }
}
