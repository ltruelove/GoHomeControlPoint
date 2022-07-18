#ifndef PAGE_TEXT
#define PAGE_TEXT

  const char wifi_index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML>
  <html>GoHome Node WiFi Selection
  <p><a href='/wifi-setup'>Go To WiFi Form</a></p>
  <p><a href='/clear'>Clear Preferences (CAREFUL!)</a></p>
  </html>)rawliteral";

  const char wifi_select_form[] PROGMEM = R"rawliteral(<!DOCTYPE HTML>
  <html>
    <h3>GoHome Control Point WiFi Setup</h3>
    <p>%IPPLACEHOLDER%</p>
    <form method='get' action='setting'>
    <table>
        <tr>
            <td width='100'><label>SSID: </label></td>
            <td>%WIFIOPTIONS%</td>
        </tr>
        <tr>
            <td><label>Key: </label></td>
            <td><input type='password' name='pass' length=64></td>
        </tr>
        <tr>
            <td><label>Control Point Name: </label></td>
            <td><input type='text' name='name'></td>
        </tr>
        <tr>
            <td><label>API Host: </label></td>
            <td><p>http:// <input type='text' name='apiHost' length=32></p></td>
        </tr>
        <tr>
            <td><label>API PORT: </label></td>
            <td><input type='number' name='apiPort'  length=5></td>
        </tr>
        <tr>
            <td>&nbsp;</td>
            <td><input type='submit'></td>
        </tr>
    </table>
    </form>
    </html>
  )rawliteral";

  const char register_index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML>
  <html>GoHome Node Registration
    <p><a href='/register'>Go To Registration Form</a></p>
    <p><a href='/clear'>Clear Preferences (CAREFUL!)</a></p>
    </html>)rawliteral";

const char register_control_point_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML>
    <html>
   <head>
      <script type='text/javascript'>
        var apiHost = '%APIHOST%';
      </script>
    <script src='https://code.jquery.com/jquery-3.6.0.min.js' integrity='sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=' crossorigin='anonymous'></script>
    <script type='text/javascript' src='%APIHOST%/js/registerControlPoint.js'></script>
    <h3>GoHome Control Point Registration</h3>
    <form method='get' action='registerControlPoint'>
    <input type='hidden' id='mac' value='%CONTROLPOINTMAC%'>
    <input type='hidden' id='controlPointName' value='%CONTROLPOINTNAME%'>
    <input type='hidden' id='controlPointIp' value='%CONTROLPOINTIP%'>
    <table>
        <tr>
            <td>&nbsp;</td>
            <td><input type='submit' value='Register With API'></td>
        </tr>
    </table>
    </form>

    </html>)rawliteral";
#endif