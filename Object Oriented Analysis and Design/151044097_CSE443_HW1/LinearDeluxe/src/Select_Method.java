import javafx.scene.control.ChoiceBox;

import java.lang.reflect.Method;

/**
 * Created by ORHAN on 25.10.2018.
 */
public class Select_Method {

    private LinearSolverDeluxe selected_method;

    public ChoiceBox<String > Methods;

    /**
     *Constructor.ChoiceBox is initialised here and filled with posible choises.
     * A listener is also activated for chances in the choicebox.
     */
    Select_Method(){
        Methods = new ChoiceBox<>();
        Methods.getItems().add("Gauss Elimination");
        Methods.getItems().add("Matrix inverse");
        Methods.setValue("Gauss Elimination");
        change_method(Methods.getValue());
        Methods.getSelectionModel().selectedItemProperty().addListener((v,oldValue,newValue) -> change_method(newValue));
    }
    /**
     *
     * @param newValue
     * String comes from choice box.It contains choices like inverse matrix method or gaussian
     * elimination.Every change triggers this function and newValues is the new choice of method.
     */
    private void change_method(String newValue){
        if(newValue.equals("Gauss Elimination"))
            selected_method=new Gaus_Elimination();

        if(newValue.equals("Matrix inverse"))
            selected_method=new Matrix_Inverse();

    }

    /**
     *
     * @param A  It is a double matrix.It contains the constants of unknown variables.Like 2x+3y+5z is 2 , 3 5
     *           and so on.
     * @param b  It is the results vector of linear equations.
     * @return
     *  It returns the values of unknown variables.
     */
    public double [] getResult(double [][]A,double[]b){

        return selected_method.getResult(A,b);

    }


}
