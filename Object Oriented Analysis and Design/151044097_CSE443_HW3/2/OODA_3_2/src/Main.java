public class Main {

    public static void main(String[] args) {


        Mail_Adress mail=new Mail_Adress("orhancelik@gmail.com","orhan çelik");
        Mail_Adress mail_2=new Mail_Adress("ahmetcelik@gmail.com","ahmet çelik");
        MailGroup grup_A=new MailGroup(new Mail_Adress("grup_A@gmail.com","Grup_A"));
        MailGroup grup_B=new MailGroup(new Mail_Adress("grup_B@gmail.com","Grup_B"));
        grup_A.Add(mail);
        grup_A.Add(mail_2);
        grup_B.Add(grup_A);
        mail.Display();
        System.out.println("////////////////////////////");
        mail_2.Display();
        System.out.println("////////////////////////////");
        grup_A.Display();
        System.out.println("////////////////////////////");
        grup_B.Display();

    }
}
