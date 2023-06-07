package com.example.iotprojectreal.ui

import android.content.Intent
import android.os.Bundle
import com.example.android_resapi.ui.apicall.GetThingShadow
import androidx.appcompat.app.AppCompatActivity
import com.example.android_resapi.ui.MainActivity
import com.example.iotprojectreal.databinding.ActivityTempBinding
import java.util.*

class TempActivity : AppCompatActivity() {
    lateinit var urlStr: String
    var timer: Timer? = null
    lateinit var binding : ActivityTempBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityTempBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.backButton.setOnClickListener{
            startActivity(
                Intent(this, MainActivity::class.java)
                    .setFlags(Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TOP))
        }

        val intent = intent
        urlStr = intent.getStringExtra("thingShadowURL").toString()
        timer = Timer()
        timer!!.schedule(
            object : TimerTask() {
                override fun run() {
                    GetThingShadow(this@TempActivity, urlStr,2).execute()
                }
            },
            0, 2000
        )
    }
}