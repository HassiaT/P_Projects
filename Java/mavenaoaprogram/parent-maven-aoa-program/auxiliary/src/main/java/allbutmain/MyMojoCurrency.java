package allbutmain;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;


@Mojo(name = "read-api-configuration")
public class MyMojoCurrency extends AbstractMojo {

    @Parameter(property = "mylogger")
    private static Log logger;

    @Parameter(property = "${configfile}", readonly = true)
    private String configfile;

    @Parameter(property = "myproject", defaultValue = "${project}", readonly = true)
    private MavenProject mydependentproject;

    private FileInputStream fileinput;

    private Properties properties;

    public MavenProject getMyDependentProject() {
        return mydependentproject;
    }

    public void setMyDependentProject(MavenProject mydependentproject) {
        this.mydependentproject = mydependentproject;
    }

    public void setFileInput(FileInputStream fileinput) {
        this.fileinput = fileinput;
    }

    public static void setLogger(Log logger) {
        MyMojoCurrency.logger = logger;
    }

    public void setConfigFile(String configfile) {
        this.configfile = configfile;
    }

    public void setProperties(Properties properties) {
        this.properties = properties;
    }

    public Properties getProperties()
    {
        return properties;
    }

    public MyMojoCurrency() {
        logger = getLog();
        logger.info("Inside constructor without parameter in class MyMojoCurrency");
        this.properties = new Properties();
    }


    public MyMojoCurrency(String config) {
        this();
        this.configfile = config;
        try {
            File building_file = new File("");
            String split = building_file.separator;
            String file_path = building_file.getAbsolutePath() + split + "" + split + "src" + split + "resources" + split;
            file_path += this.configfile;
            this.setFileInput(new FileInputStream(file_path));
            logger.info("Input file is : " + file_path);
        } catch (Exception e) {
            System.out.println("Constructor MyMojoCurrency: " + e.getMessage());
            logger.error("Exception raised in MyMojoCurrency" + e.getCause().toString());
        }
    }

    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {
        logger.info("Executing MyMojoCurrency execute function");
        try {
            Properties local_properties = new Properties();
            local_properties.load(this.fileinput);
            this.properties = local_properties;

//            for (Object key : this.properties.keySet()) {
//                mydependentproject.setProperty((String) key, (String) fileProperties.get(key));
//            }
//
//            this.properties.set
            this.properties.list(System.out);

            //    project.getProperties().list(System.out);
        } catch (FileNotFoundException e) {
            throw new MojoFailureException("The file " + this.fileinput.toString() + " was not found!", e);
        } catch (IOException e) {
            logger.error("");
        }
    }
}
