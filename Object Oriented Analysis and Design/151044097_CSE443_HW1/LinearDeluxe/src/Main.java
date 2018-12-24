/**
 * Created by ORHAN on 25.10.2018.
 */

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javax.xml.soap.Text;
import java.util.ArrayList;
import java.util.Random;

    public class Main extends Application {

        private int size=3;
        private VBox layout;
        private HBox hLayout;
        private Button button;
        private Scene scene;
        private GridPane A;
        private GridPane b;
        private GridPane results_Panel;
        private double[][] A_Matrix;
        private double [] b_Matrix;

        private Select_Method method;

        /**
         *
         * @param primaryStage Entire UI window tray.
         */
        @Override
        public void start(Stage primaryStage) {

            button=new Button("Get Result");

            method=new Select_Method();

            ChoiceBox<Integer> combo = new ChoiceBox<>();
            combo.getItems().add(2);
            combo.getItems().add(3);
            combo.getItems().add(4);
            combo.getItems().add(5);
            combo.getItems().add(6);
            combo.getItems().add(7);
            combo.getItems().add(8);
            combo.getItems().add(9);
            combo.setValue(size);




            matrix(size,primaryStage,combo,method.Methods);
            combo.getSelectionModel().selectedItemProperty().addListener((v,oldValue,newValue) -> matrix(newValue,primaryStage,combo,method.Methods));

        }

        public static void main(String[] args) {
            launch(args);
        }

        /**
         *
         * @param size   Size of matrix dimansions.
         * @param primaryStage  Entire UI window.
         * @param combo  Choicebox of matrix size.
         * @param method Choicebox of mathematical method of calculating the result.
         */
        public void matrix(int size,Stage primaryStage,ChoiceBox<Integer> combo ,ChoiceBox<String> method){

            button.setOnAction(e -> Solver());

            layout = new VBox(10);
            layout.setPadding(new Insets(10,10,10,10));
            hLayout = new HBox(10);
            hLayout.setPadding(new Insets(10,10,10,10));
            A = new GridPane();
            b = new GridPane();
            results_Panel=new GridPane();

            for(int y = 0; y < size; y++){
                for(int x = 0; x < size; x++){

                    // Create a new TextField in each Iteration
                    TextField tf = new TextField();
                    tf.setPrefHeight(30);
                    tf.setPrefWidth(30);
                    tf.setAlignment(Pos.CENTER);
                    tf.setEditable(true);
                    tf.setText("");

                    // Iterate the Index using the loops
                    A.setRowIndex(tf,y);
                    A.setColumnIndex(tf,x);
                    A.getChildren().add(tf);
                }
            }

            for (int i=0;i<size;i++){
                TextField tf = new TextField();
                tf.setPrefHeight(30);
                tf.setPrefWidth(30);
                tf.setAlignment(Pos.CENTER);
                tf.setEditable(true);
                tf.setText("");

                b.setRowIndex(tf,i);
                b.setColumnIndex(tf,0);
                b.getChildren().add(tf);

            }
            hLayout.getChildren().addAll(A,b,method);
            layout.getChildren().addAll(hLayout,combo,button);

            scene = new Scene(layout, 500, 500);
            primaryStage.setTitle("Linear Solver Deluxe");
            primaryStage.setScene(scene);
            primaryStage.show();
        }

        /**
         *Activated by Get_Result button.It prints the results onto UI.
         */
        private void Solver(){

            A_Matrix=new double[size][size];
            b_Matrix=new double[size];
            double [] result=new double[size];
            fill_Matrixes();

            result=method.getResult(A_Matrix,b_Matrix);

            TextField tf = new TextField();
            tf.setPrefHeight(30);
            tf.setPrefWidth(300);
            tf.setAlignment(Pos.CENTER);
            tf.setEditable(true);
            tf.setText("");

            System.out.println("Results");
            for (int i=0;i<size;i++){
                tf.setText(tf.getText() + " " + result[i]);
                //System.out.print(result[i]+ " ");
            }
            System.out.println(tf.getText());
            layout.getChildren().remove(results_Panel);
            results_Panel=new GridPane();
            results_Panel.setRowIndex(tf,0);
            results_Panel.setColumnIndex(tf,0);
            results_Panel.getChildren().add(tf);

            layout.getChildren().add(results_Panel);


        }

        /**
         *It reads texts from user interface and parse them into  arrays.Like A_matrix and b_Matrix.
         */
        private void fill_Matrixes(){
            System.out.println("A_Matrix");
            for (int i=0;i<size;i++){

                for (int j=0;j<size;j++){

                    A_Matrix[i][j]=Double.parseDouble(((TextField)A.getChildren().get(i*size+j)).getText());
                    System.out.print(A_Matrix[i][j]+" ");
                }
                System.out.println();
            }

            System.out.println("b_Matrix");
            for(int i=0;i<size;i++){

                b_Matrix[i]=Double.parseDouble(((TextField)b.getChildren().get(i)).getText());
                System.out.print(b_Matrix[i]+" ");
            }
            System.out.println();
        }


    }

