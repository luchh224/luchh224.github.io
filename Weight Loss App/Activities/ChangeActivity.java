package com.zybooks.weightlosskcl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class ChangeActivity extends AppCompatActivity {

    //This is going to create variables to edit text
    private EditText dateEdt, weightEdt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.change_screen);

        dateEdt = findViewById(R.id.editTextDate);
        weightEdt = findViewById(R.id.NewWeightChange);

        Button switchToMainActivity;
        //This button click is to change a weight. Once the user clicks the button, the user will be taken back to the Main Screen
        //and is prompted with a message VIA Toast
        switchToMainActivity = findViewById(R.id.changeRecord_button);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String date = dateEdt.getText().toString();
                String weight = weightEdt.getText().toString();

                if (date.isEmpty() && weight.isEmpty()) {
                    Toast.makeText(ChangeActivity.this, "Please fill in all of the fields", Toast.LENGTH_SHORT).show();
                    return;
                }

                startActivity(new Intent(ChangeActivity.this, MainActivity.class));
                Toast.makeText(ChangeActivity.this, "Record Changed Successfully!", Toast.LENGTH_SHORT).show();
            }
        });
        //This button click is to cancel the current process and take you back to the main screen
        switchToMainActivity = findViewById(R.id.change_cancelButton);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(ChangeActivity.this, MainActivity.class));
            }
        });
    }
}
