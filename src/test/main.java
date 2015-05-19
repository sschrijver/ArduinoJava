package test;

public class main
{
    public static void main(String[] args) throws Exception
    {
        Connectie connectie = new Connectie();
        Aansturing aansturing = new Aansturing(connectie);
        if (connectie.initialize())
        {
            aansturing.stuur("-1,-5");
            aansturing.stuur("2,3");
            aansturing.stuur("-1,0");
            connectie.close();
        }

    }

}
