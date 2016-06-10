package com.januszsoft.bikerental.backend.config;

import com.januszsoft.bikerental.backend.dao.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.datasource.DriverManagerDataSource;
import org.springframework.web.servlet.ViewResolver;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;
import org.springframework.web.servlet.view.InternalResourceViewResolver;

import javax.sql.DataSource;

@Configuration
@ComponentScan(basePackages="com.januszsoft.bikerental")
@EnableWebMvc
public class MvcConfiguration extends WebMvcConfigurerAdapter{

  @Bean
  public ViewResolver getViewResolver(){
    InternalResourceViewResolver resolver = new InternalResourceViewResolver();
    resolver.setPrefix("/WEB-INF/views/");
    resolver.setSuffix(".jsp");
    return resolver;
  }

  @Override
  public void addResourceHandlers(ResourceHandlerRegistry registry) {
    registry.addResourceHandler("/resources/**").addResourceLocations("/resources/");
  }

  @Bean
  public DataSource getDataSource() {
    DriverManagerDataSource dataSource = new DriverManagerDataSource();
    dataSource.setDriverClassName("org.postgresql.Driver");
    dataSource.setUrl("jdbc:postgresql://10.100.100.150:5432/bikerental");
    dataSource.setUsername("vagrant");
    dataSource.setPassword("vagrant");

    return dataSource;
  }

  @Bean
  public UsserDaoImpl getUsserDao() {
    return new UsserDaoImpl(getDataSource());
  }

  @Bean
  public StationDaoImpl getStationDao() {
    return new StationDaoImpl(getDataSource());
  }

  @Bean
  public ServiceDaoImpl getServiceDao() {
    return new ServiceDaoImpl(getDataSource());
  }

  @Bean
  public ServicemanDaoImpl getServicemanDao() {
    return new ServicemanDaoImpl(getDataSource());
  }

  @Bean
  public RentDaoImpl getRentDao() {
    return new RentDaoImpl(getDataSource());
  }

  @Bean
  public PaymentDaoImpl getPaymentDao() {
    return new PaymentDaoImpl(getDataSource());
  }

  @Bean
  public IssueDaoImpl getIssueDao() {
    return new IssueDaoImpl(getDataSource());
  }

  @Bean
  public BikeDaoImpl getBikeDao() {
    return new BikeDaoImpl(getDataSource());
  }

  @Bean
  public SessionDaoImpl getSessioneDao() {
    return new SessionDaoImpl(getDataSource());
  }
}
