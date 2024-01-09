package fi.tuni.prog3.calc;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;


/**
 * JavaFX App
 */
public class Calculator extends Application {

    @Override
    public void start(Stage primaryStage) {
        TextField fieldOp1 = new TextField();
        fieldOp1.setId("fieldOp1");
        TextField fieldOp2 = new TextField();
        fieldOp2.setId("fieldOp2");

        Label labelOp1 = new Label("First operand:");
        labelOp1.setId("labelOp1");
        Label labelOp2 = new Label("Second operand:");
        labelOp2.setId("labelOp2");

        Button btnAdd = new Button("Add");
        btnAdd.setId("btnAdd");
        Button btnSub = new Button("Subtract");
        btnSub.setId("btnSub");
        Button btnMul = new Button("Multiply");
        btnMul.setId("btnMul");
        Button btnDiv = new Button("Divide");
        btnDiv.setId("btnDiv");

        // Tuloskenttä
        Label fieldRes = new Label();
        fieldRes.setId("fieldRes");
        fieldRes.setBackground(new Background(new BackgroundFill(Color.WHITE, CornerRadii.EMPTY, Insets.EMPTY)));

        // Tapahtumankäsittelijät napeille
        btnAdd.setOnAction(e -> calculate(fieldOp1, fieldOp2, fieldRes, '+'));
        btnSub.setOnAction(e -> calculate(fieldOp1, fieldOp2, fieldRes, '-'));
        btnMul.setOnAction(e -> calculate(fieldOp1, fieldOp2, fieldRes, '*'));
        btnDiv.setOnAction(e -> calculate(fieldOp1, fieldOp2, fieldRes, '/'));
        

        Label labelRes = new Label("Result:");
        labelRes.setId("labelRes");

        GridPane grid = new GridPane();
        grid.add(labelOp1, 0, 0);
        grid.add(fieldOp1, 1, 0);
        grid.add(labelOp2, 0, 1);
        grid.add(fieldOp2, 1, 1);
        grid.add(btnAdd, 0, 2);
        grid.add(btnSub, 1, 2);
        grid.add(btnMul, 0, 3);
        grid.add(btnDiv, 1, 3);
        grid.add(labelRes, 0, 4);
        grid.add(fieldRes, 1, 4);

        Scene scene = new Scene(grid, 300, 250);

        primaryStage.setTitle("Calculator");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void calculate(TextField op1, TextField op2, Label result, char operator) {
        try {
            double operand1 = Double.parseDouble(op1.getText());
            double operand2 = Double.parseDouble(op2.getText());
            double calcResult = 0;

            switch (operator) {
                case '+':
                    calcResult = operand1 + operand2;
                    break;
                case '-':
                    calcResult = operand1 - operand2;
                    break;
                case '*':
                    calcResult = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        calcResult = operand1 / operand2;
                    } else {
                        result.setText("Error: Divide by zero");
                        return;
                    }
                    break;
            }
            result.setText(String.valueOf(calcResult));
        } catch (NumberFormatException e) {
            result.setText("Error: Invalid number");
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}