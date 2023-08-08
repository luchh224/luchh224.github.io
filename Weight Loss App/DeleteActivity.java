package com.zybooks.weightlosskcl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class DeleteActivity extends AppCompatActivity {

    //This is going to create variables to edit text
    private EditText deleteEdt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.delete_screen);

        //This is going to initialize our variables. Our edit text views are already assigned names
        //and I will use those on the findViewByID method
        deleteEdt = findViewById(R.id.editTextDate);

        Button delete;
        Button switchToMainActivity;


        switchToMainActivity = findViewById(R.id.cancelButton);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(DeleteActivity.this, MainActivity.class));
            }
        });

        delete = findViewById(R.id.deleteRecord_button);
        delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String delete = deleteEdt.getText().toString();

                //This is going to be the if statement to check if the fields have all been filled in before proceeding to prevent a login
                //from happening where nothing is filled in
                if (delete.isEmpty()) {
                    Toast.makeText(DeleteActivity.this, "Please fill in all of the fields", Toast.LENGTH_SHORT).show();
                    return;
                }

                startActivity(new Intent(DeleteActivity.this, MainActivity.class));
                Toast.makeText(DeleteActivity.this, "Entry Successfully Deleted!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}

