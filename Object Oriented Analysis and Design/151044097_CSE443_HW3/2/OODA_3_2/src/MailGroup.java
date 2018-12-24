import java.util.ArrayList;

/**
 * Created by ORHAN on 10.12.2018.
 */
public class MailGroup extends Mail_Adress {

    ArrayList<Mail_Adress> group;

    MailGroup(Mail_Adress ad){
        super(ad.adress,ad.owner_Name);

        group=new ArrayList<Mail_Adress>();
    }
    void Add(Mail_Adress mail){
        group.add(mail);

    }
    public void Display(){
        super.Display();
        for (int i = 0; i <group.size() ; i++) {

            group.get(i).Display();
        }
    }
}
