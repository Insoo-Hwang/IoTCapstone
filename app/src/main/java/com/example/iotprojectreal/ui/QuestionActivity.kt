package com.example.iotprojectreal.ui

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.android_resapi.ui.MainActivity
import com.example.android_resapi.ui.apicall.GetThingShadow
import com.example.iotprojectreal.databinding.ActivityQuestionBinding
import java.util.*

class QuestionActivity : AppCompatActivity(){
    lateinit var urlStr: String
    var timer: Timer? = null
    lateinit var binding : ActivityQuestionBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityQuestionBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.backButton.setOnClickListener{
            startActivity(
                Intent(this, MainActivity::class.java)
                    .setFlags(Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TOP))
        }

        val intent = intent
        urlStr = intent.getStringExtra("ultrasonicShadow").toString()
        timer = Timer()
        timer!!.schedule(
            object : TimerTask() {
                override fun run() {
                    GetThingShadow(this@QuestionActivity, urlStr,1).execute()
                }
            },
            0, 2000
        )
    }
}